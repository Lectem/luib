//
// Created by Lectem on 14/04/2015.
//

#include "UI/Container.hpp"
#include <algorithm>
namespace luib {

    Container::Container(int x, int y, int w, int h,u32 bgColor) : Element(x, y, w, h,bgColor)
    {

    }


    Container::~Container()
    {

    }


    void Container::attach(Element_shared_ptr element)
    {
        children.emplace_back(element);
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

    void Container::draw() const
    {
        Element::draw();
        for(auto &e : children)
        {
            if(e.use_count())e->draw();
        }
    }


    void Container::onClick()
    {
        for(auto it = children.begin();it != children.end() ; ++it)
        {
            if(it->use_count() == 0)
            {
                it = children.erase(it);
            }
            else if((*it)->isTouched()) (*it)->onClick();
        }
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
}