//
// Created by Lectem on 14/04/2015.
//

#include "UI/Container.hpp"
#include <algorithm>
#include <luib.hpp>
#include <3ds/services/hid.h>

namespace luib {

    Container::Container(int x, int y, int w, int h,u32 bgColor) : Element(x, y, w, h,bgColor)
    {

    }


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
        children.push_back(element);
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
            for (auto childPtrIt = children.begin(); childPtrIt != children.end(); ++childPtrIt)
            {
                if (childPtrIt->get() == element)
                {
                    (*childPtrIt)->_upper = nullptr;
                    onDetach(childPtrIt->get());
                    children.erase(childPtrIt);
                    return;
                }
            }
        }
        requestLayout();
    }

    void Container::bringToFront(Element *element)
    {
        const size_t size=children.size();
        for(size_t i=0;i<size;++i)
        {
            if(children[i].get() == element && i != size)
            {
                auto childToBringFront = children[i];
                size_t j;
                for(j = i; j+1 < size; ++j)
                {
                    children[j]=std::move(children[j+1]);
                }
                children[j] = childToBringFront;
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
        for(auto it =children.cbegin();it!=children.cend();++it)
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
        for(int child = children.size()-1;child>=0;--child)
        {

            Point relativeSytlusPos = touchEvent.viewPos;
            relativeSytlusPos.x -= children[child]->_aabb.x;
            relativeSytlusPos.y -= children[child]->_aabb.y;
            TouchEvent dispatchedTouchEvent = touchEvent;
            dispatchedTouchEvent.viewPos = relativeSytlusPos;
            if (children[child]->_aabb.contains(touchEvent.viewPos) &&
                children[child]->findFocusedElement(currentFocus, dispatchedTouchEvent))
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
        for(Element_shared_ptr e:children)
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
        children.clear();
    }

    void Container::onAttach(Element *element)
    {
        element->_bringToFrontOnFocus |= _bringToFrontOnFocus;
    }

    void Container::onLayout(Rectangle const &coordinates)
    {
        for(auto& childPtr:children)
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
}