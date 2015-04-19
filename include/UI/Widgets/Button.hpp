//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "UI/Element.hpp"

namespace luib {
    class Button : public Element
    {

    public:
        Button(){}
        ~Button(){printf("Button freed\n");}
        Button(int x, int y, int w, int h);
    };
    using Button_shared_ptr = std::shared_ptr<Button>;

}

