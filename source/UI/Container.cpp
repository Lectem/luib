//
// Created by Lectem on 14/04/2015.
//

#include "UI/Container.hpp"
#include <algorithm>
#include <luib.hpp>
#include <3ds/services/hid.h>

namespace luib {

    Container::Container(int x, int y, int w, int h,u32 bgColor) :
            Element(x, y, w, h,bgColor) { }


    Container::Container(LayoutParams layoutParams):
            Element(layoutParams) { }

    Container::~Container()
    {

    }


    void Container::attach(Element_shared_ptr element)
    {
        if(element->_upper)
        {
            fprintf(stderr,"Can't attach a view to two parents\n");
            return;
        }
        element->_upper = this;
        if (_root != nullptr)element->_root = _root;
        else element->_root = this;
        element->_depthLevel = _depthLevel +1;
        element->requestLayout();
        _children.push_back(element);
        onAttach(element.get());
    }

    void Container::detach(Element_shared_ptr element)
    {
        detach(element.get());
    }

    void Container::detach(Element * const element)
    {
        if(element != nullptr)
        {
            ResetFocus();
            for (auto childPtrIt = _children.begin(); childPtrIt != _children.end(); ++childPtrIt)
            {
                if (childPtrIt->get() == element)
                {
                    (*childPtrIt)->_upper = nullptr;
                    onDetach(childPtrIt->get());
                    _children.erase(childPtrIt);
                    return;
                }
            }
        }
        requestLayout();
    }

    void Container::bringToFront(Element *element)
    {
        const size_t size= _children.size();
        for(size_t i=0;i<size;++i)
        {
            if(_children[i].get() == element && i != size)
            {
                auto childToBringFront = _children[i];
                size_t j;
                for(j = i; j+1 < size; ++j)
                {
                    _children[j]=std::move(_children[j+1]);
                }
                _children[j] = childToBringFront;
                break;
            }
        }
    }
    void Container::onDraw(Canvas &canvas) const
    {
        //FIXME:probably wrong

        Canvas oldCanvas = canvas;
        const Point &oldOrigin = oldCanvas.getOrigin();
        //printf("old canvas origin : %d %d\n",oldOrigin.x,oldOrigin.y);
        //printf("frame : %d %d %d %d \n",oldCanvas.getFrame().x,oldCanvas.getFrame().y, oldCanvas.getFrame().w,oldCanvas.getFrame().h);
        //printf("_aabb : %d %d %d %d\n",_aabb.x,_aabb.y,_aabb.w,_aabb.h);
        Element::onDraw(canvas);
        for(auto it = _children.cbegin();it!= _children.cend();++it)
        {
            Element_shared_ptr child = *it;
            //Make a copy of the child aabb
            Rectangle childAABB = child->_aabb+oldOrigin;
            canvas.setOrigin(childAABB.x,childAABB.y);
            Rectangle clipArea =oldCanvas.getFrame();// {oldOrigin.x,oldOrigin.y,getWidth(),getHeight()};
            //printf("|*Before clip %d %d %d %d\n",childAABB.x,childAABB.y,childAABB.w,childAABB.h);
            //printf("|*clip  with  %d %d %d %d\n",clipArea.x,clipArea.y,clipArea.w,clipArea.h);
            childAABB.clip(clipArea);
            //printf("|*after clip  %d %d %d %d\n",childAABB.x,childAABB.y,childAABB.w,childAABB.h);
            canvas.setFrame(childAABB);
            //printf("|-drawing element at %d %d\n",canvas.getOrigin().x,canvas.getOrigin().y);
            //printf("|-frame :     %d %d %d %d\n",canvas.getFrame().x,canvas.getFrame().y,canvas.getFrame().w,canvas.getFrame().h);
            if((*it).use_count())(*it)->draw(canvas);
        };
        canvas.setFrameAndOrigin({oldOrigin.x,oldOrigin.y,getWidth(),getHeight()});
        canvas = oldCanvas;
    }


    void Container::onTouchEvent(const TouchEvent &touchEvent)
    {
        Element::onTouchEvent(touchEvent);
    }


    bool Container::findFocusedElement(Element *&currentFocus, TouchEvent &touchEvent)
    {
        for(int child = _children.size()-1;child>=0;--child)
        {

            Point relativeSytlusPos = touchEvent.viewPos;
            relativeSytlusPos.x -= _children[child]->_aabb.x;
            relativeSytlusPos.y -= _children[child]->_aabb.y;
            TouchEvent dispatchedTouchEvent = touchEvent;
            dispatchedTouchEvent.viewPos = relativeSytlusPos;
            if (_children[child]->_aabb.contains(touchEvent.viewPos) &&
                _children[child]->findFocusedElement(currentFocus, dispatchedTouchEvent))
            {
                touchEvent = dispatchedTouchEvent;
                return true;
            }
        }
        return Element::findFocusedElement(currentFocus, touchEvent);
    }

    void Container::move(int x, int y)
    {
        Element::move(x, y);
        for(Element_shared_ptr e:_children)
        {
            moveChild(e.get(),x,y);
        }
    }

    void Container::moveTo(int x, int y)
    {
        int dx = x- _aabb.x;
        int dy = y- _aabb.y;
        move(dx, dy);
    }

    void Container::moveChild(Element * child,int x, int y)
    {
        //Do not move out of bound
        if(child->_aabb.x+x+child->_aabb.w>=getWidth())
            child->_aabb.x=getWidth()-child->_aabb.w;
        else if(child->_aabb.x+x<0)
            child->_aabb.x=0;
        else
            child->_aabb.x+=x;


        if(child->_aabb.y+y+child->_aabb.h>=getHeight())
            child->_aabb.y=getHeight()-child->_aabb.h;
        else if(child->_aabb.y+y<0)
            child->_aabb.y=0;
        else
            child->_aabb.y+=y;
        child->requestLayout();
    }

    void Container::moveChildTo(Element * child,int x, int y)
    {
        int dx = x- _aabb.x;
        int dy = y- _aabb.y;
        moveChild(child,dx, dy);
    }

    void Container::clean()
    {
        _children.clear();
    }

    void Container::onAttach(Element *element)
    {
        element->_bringToFrontOnFocus |= _bringToFrontOnFocus;
    }

    void Container::onLayout(Rectangle const &coordinates)
    {
        for(auto& childPtr:_children)
        {
            //TODO finish and correct this
            childPtr->layout({0,0,getWidth(),getHeight()});
        }
    }

    void Container::setChildAABB(Element *child, Rectangle const &aabb)
    {
        child->_aabb=aabb;
    }

    Rectangle &Container::getChildAABB(Element *child)
    {
        return child->_aabb;
    }
    Rectangle const &Container::getChildAABB(Element *child) const
    {
        return child->_aabb;
    }

    void Container::onDetach(Element *element)
    {

    }

    void Container::measureChildren(sizeConstraint width, sizeConstraint height)
    {
        for(auto &childPtr  : _children)
        {
            if(childPtr->_visibility != GONE)
            {
                measureChild(childPtr,width,height);
            }
        }
    }


    sizeConstraint Container::getChildSizeContraint(sizeConstraint constraint,int padding,int childParam)
    {

        int size = std::max(0,constraint.value-padding);
        sizeConstraint result(size,sizeConstraint::NOT_SPECIFIED);
        switch (constraint.type)
        {
            //Our size is limited
            case sizeConstraint::AT_MOST:
                //The child wants to be of our size, but we don't have it yet
                //So we'll just make sure it won't be bigger than us
                if(childParam == LayoutParams::MATCH_PARENT)
                {
                    result.type = sizeConstraint::AT_MOST;
                }
                //Child will determine its own size, but musn't be bigger the us
                else if(childParam == LayoutParams::WRAP_CONTENT)
                {
                    result.type = sizeConstraint::AT_MOST;
                }
                //The child asked for a size, so... whatever
                else
                {
                    result.value = childParam;
                    result.type = sizeConstraint::NOT_SPECIFIED;
                }
                break;
            //We know our size
            case sizeConstraint::EXACTLY:
                if(childParam == LayoutParams::WRAP_CONTENT)
                {
                    result.type=sizeConstraint::AT_MOST;
                }
                else
                {
                    result.type=sizeConstraint::EXACTLY;
                }
                break;
            // No limits !
            case sizeConstraint::NOT_SPECIFIED:
                //The child wants a specific size, just give him
                if(childParam >=0)
                {
                    result.value = childParam;
                    result.type = sizeConstraint::EXACTLY;
                }
                //Otherwise just let him choose it
                else
                {
                    result.value=0;
                    result.type=sizeConstraint::NOT_SPECIFIED;
                }
                break;
        }
        //printf("getChildSizeContraint = %d %d \n",result.value,result.type);
        return result;
    }

    void Container::measureChild(Element_shared_ptr child, sizeConstraint width, sizeConstraint height)
    {
        LayoutParams childLayoutParams = child->getLayoutParams();
        if(childLayoutParams.width == LayoutParams::DEFAULT)
        {
            childLayoutParams.width = getDefaultLayoutParams();
        }
        if(childLayoutParams.height == LayoutParams::DEFAULT)
        {
            childLayoutParams.height = getDefaultLayoutParams();
        }
        width = getChildSizeContraint(width,_padding.left+_padding.right,childLayoutParams.width);
        height = getChildSizeContraint(height,_padding.top+_padding.bot,childLayoutParams.height);
        child->measure(width,height);
    }

    void Container::onMeasure(sizeConstraint width, sizeConstraint height)
    {
        //printf("Container::onMeasure\n");
        measureChildren(width,height);
        Element::onMeasure(width, height);
    }
}