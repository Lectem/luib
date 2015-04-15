//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "UI/Element.hpp"
#include <string>
namespace luib {
    class Text : public Element
    {

    public:
        Text(int x, int y, int w, int h,std::string text);

        void draw();

    private:
        std::string text;
    };
}

