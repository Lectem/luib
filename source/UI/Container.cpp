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
        element->upper = this;
        if (root != nullptr)element->root = root;
        else element->root = this;
        element->depthLevel = depthLevel+1;
        children.push_front(element);
    }

    void Container::detach(Element_shared_ptr element)
    {
        for(auto &e:children)
        {
            if(e == element)
            {
                e.reset();
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
    void Container::draw() const
    {
        Element::draw();
        for(auto it =children.rbegin();it!=children.rend();++it)
        {
            if((*it).use_count())(*it)->draw();
        }
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

    void Container::getFocusedElement(Element* & currentFocus)
    {
        Element::getFocusedElement(currentFocus);
        for(auto it = children.begin();it!=children.end();++it)
        {
            if((*it)->aabb.contains(touch.px,touch.py))
            {
                (*it)->getFocusedElement(currentFocus);
            }
        }
    }

    void Container::move(int x, int y)
    {
        Element::move(x, y);
        for(Element_shared_ptr e:children)
        {
            e->move(x,y);
        }
    }

    void Container::moveTo(int x, int y)
    {
        int dx = x-aabb.x;
        int dy = y-aabb.y;
        Element::move(dx, dy);
        for(Element_shared_ptr e:children)
        {
            e->move(dx,dy);
        }
    }
}