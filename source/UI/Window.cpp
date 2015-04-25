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

    Window::Window(int x, int y, int w, int h,u32 bgColor) :
            Container(x, y, w, h,bgColor)
    {
        Element::bringToFrontOnFocus = true;
    }

    void Window::onClick()
    {
        if(titleBarAABB().contains(touch.px,touch.py))
        {
            touchOffset.px = touch.px-aabb.x;
            touchOffset.py = touch.py-aabb.y;
            isGrabbed = true;
        }
        else if (closeButtonAABB().contains(touch.px,touch.py))
        {
            bgColor^=0xFF000000;
            upper->detach(this);
        }
        else
        {
            printf("Window clicked\n");
            Container::onClick();
        }
    }

    void Window::onHold()
    {
        if(isGrabbed)
        {
            moveTo((7*(touch.px-touchOffset.px)+aabb.x)/8,
                    (7*(touch.py-touchOffset.py)+aabb.y)/8);
        }
    }
    Rectangle Window::titleBarAABB()
    {
        return Rectangle(aabb.x , aabb.y,aabb.w - topBarHeight, topBarHeight);
    }

    Rectangle Window::closeButtonAABB()
    {
        return Rectangle(aabb.x + aabb.w - topBarHeight, aabb.y, topBarHeight, topBarHeight);
    }

    void Window::onFocus()
    {

    }

    void Window::onFocusLoss()
    {
        printf("Window lost focus\n");
        isGrabbed = false;
    }

    void Window::bringToFront(Element *element)
    {
        Container::bringToFront(element);
        Element::bringToFront();
    }
}