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
        for (size_t i=0; children.size();++i)
        {
            delete children[i];
        }
    }


    void Container::draw() const
    {
        Element::draw();
        for(Element * e : children)
        {
            e->draw();
        }
    }


    void Container::onClick()
    {
        Element::onClick();
        for(Element * e : children)
        {
            if(e->isTouched())
            {
                e->onClick();
            }
        }
    }
}