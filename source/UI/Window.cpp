//
// Created by Lectem on 18/04/2015.
//
#include <luib.hpp>
#include <3ds/services/hid.h>
#include <UI/Draw.hpp>
#include "UI/Window.hpp"
namespace luib {
    void Window::draw() const
    {
        Container::draw();
        draw::rectangle(aabb.x, aabb.y, aabb.w, topBarHeight, 0x0000FFFF);
        draw::rectangle(aabb.x + aabb.w - topBarHeight, aabb.y, topBarHeight, topBarHeight, 0x00FF00FF);
    }

    Window::Window(int x, int y, int w, int h) : Container(x, y, w, h)
    {

    }

    void Window::onClick()
    {
        if (closeButtonAABB().contains(touch.px,touch.py))
        {
            bgColor^=0xFF000000;
            upper->detach(this);
        }
        else
        {
            Container::onClick();
        }
    }

    Rectangle Window::closeButtonAABB()
    {
        return Rectangle(aabb.x + aabb.w - topBarHeight, aabb.y, topBarHeight, topBarHeight);
    }
}