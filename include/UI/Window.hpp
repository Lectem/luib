//
// Created by Lectem on 18/04/2015.
//
#pragma once

#include "UI/Container.hpp"
namespace luib {

    class Window : public Container
    {
        int topBarHeight = 8;
        Rectangle closeButtonAABB();

    public:
        Window(int x, int y, int w, int h);
        virtual void draw() const override;
        virtual void onClick() override;
    };


}