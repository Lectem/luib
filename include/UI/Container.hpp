//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "Element.hpp"

namespace luib {
    class Container : public Element
    {
        std::vector<Element *> children;
    public:
        Container(int x, int y, int w, int h);
    };

}