//
// Created by Lectem on 18/04/2015.
//
#pragma once

#include "UI/Container.hpp"
namespace luib {

    class Window : public Container
    {
        int topBarHeight = 8;
        Point offset;
        Rectangle closeButtonAABB() const;
        Rectangle titleBarAABB() const;
        bool isGrabbed = false;
        touchPosition touchOffset;

    public:
        Window(int x, int y, int w, int h, u32 bgColor = RGBA8(0xFF,0xFF,0xFF,0xFF));

        virtual ~Window()
        {
            printf("Window has been closed and freed\n");
        }

        virtual void onDraw(Canvas &canvas) const override;

    protected:
        virtual void onClick() override;
        virtual void onHold() override;
        virtual void onFocus() override;
        virtual void onFocusLoss() override;


    public:
        virtual void bringToFront(Element *element) override;

    protected:
        virtual void onLayout(Rectangle const &coordinates) override;
    };


    using Window_shared_ptr = std::shared_ptr<Window>;
}