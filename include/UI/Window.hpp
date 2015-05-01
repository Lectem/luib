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
        bool isGrabbed = false;
        touchPosition touchOffset;

    public:
        Window(int x, int y, int w, int h, u32 bgColor = RGBA8(0xFF,0xFF,0xFF,0xFF));

        virtual ~Window()
        {
            printf("Window has been closed and freed\n");
        }
        template<class T, class ... Args>
        std::shared_ptr<T> add(Args &&... args);

        virtual void onDraw(Canvas &canvas) const override;

    protected:
        virtual void onClick() override;

        virtual void onHold() override;

        virtual void onFocus() override;
        virtual void onFocusLoss() override;

    public:
        virtual void bringToFront(Element *element) override;
    };


    template<class T, class ... Args>
    std::shared_ptr<T> Window::add(Args &&... args)
    {
        std::shared_ptr<T> element = Container::add<T>(std::forward<Args>(args)...);
        element->measure(_aabb.w, _aabb.h-topBarHeight);
        return element;
    }


    using Window_shared_ptr = std::shared_ptr<Window>;
}