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
        Rectangle titleBarAABB();

    public:
        Window(int x, int y, int w, int h, u32 bgColor = RGBA8(0xFF,0xFF,0xFF,0xFF));

        virtual ~Window()
        {
            printf("Window has been closed and freed\n");
        }

        virtual void draw() const override;

    protected:
        virtual void onClick() override;
    };

    using Window_shared_ptr = std::shared_ptr<Window>;
}