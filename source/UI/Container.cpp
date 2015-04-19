//
// Created by Lectem on 14/04/2015.
//

#include "UI/Container.hpp"

namespace luib {

    Container::Container(int x, int y, int w, int h) : Element(x, y, w, h)
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
        children.remove(element);
    }

    void Container::detach(Element * const element)
    {
        children.remove_if([element](Element_shared_ptr &it){ return it.get() == element;});
    }

    void Container::draw() const
    {
        Element::draw();
        for(auto e : children)
        {
            e->draw();
        }
    }


    void Container::onClick()
    {
        Element::onClick();
        for(auto e : children)
        {
            if(e->isTouched())
            {
                e->onClick();
            }
        }
    }


}