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
        children.push_front(element);
        onAttach(element.get());
    }

    void Container::detach(Element_shared_ptr element)
    {
        for(auto &child:children)
        {
            if(child == element)
            {
                onDetach(child.get());
                child.reset();
            }
        }
    }

    void Container::detach(Element * const element)
    {
        for(auto &e:children)
        {
            if(e.get() == element)
            {
                e.reset();
            }
        }
    }

    void Container::bringToFront(Element *element)
    {
        for(auto it = children.begin();it != children.end();++it)
        {
            if((*it).get() == element)
            {
                //children are in order of draw.
                //(*it).swap(children.back());
                children.splice(children.begin(),children,it);
                break;
            }
        }
    }
    void Container::onDraw(Canvas &canvas) const
    {
        Element::onDraw(canvas);
        for(auto it =children.rbegin();it!=children.rend();++it)
        {
            Element_shared_ptr child = *it;
            canvas.setOrigin(child->_aabb.x, child->_aabb.y);
            if((*it).use_count())(*it)->draw(canvas);
        }
        canvas.setOrigin(_aabb.x, _aabb.y);
    }


    void Container::onClick()
    {
        Element::onClick();
    }


    void Container::update()
    {
        for(auto it = children.begin();it != children.end() ; ++it)
        {
            if(it->use_count() == 0)
            {
                it = children.erase(it);
            }
            else (*it)->update();
        }
    }

    bool Container::getFocusedElement(Element *&currentFocus)
    {
        bool newFocus = false;
        for(auto it = children.begin();it!=children.end() && !newFocus;++it)
        {
            if((*it)->_aabb.contains(touch.px,touch.py))
            {
                newFocus = (*it)->getFocusedElement(currentFocus);
            }
        }
        newFocus|=Element::getFocusedElement(currentFocus);
        return newFocus;
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

    void Container::layout(Rectangle const &coordinates)
    {
        for(auto& childPtr:children)
        {
            //TODO finish and correct this
            childPtr->layout(coordinates);
        }
    }

    void Container::setChildAABB(Element *child, Rectangle const &aabb)
    {
        child->_aabb=aabb;
    }

    Rectangle const &Container::getChildAABB(Element *child)
    {
        return child->_aabb;
    }

    void Container::onDetach(Element *element)
    {

    }
}