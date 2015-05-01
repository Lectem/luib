//
// Created by Lectem on 18/04/2015.
//
#include <luib.hpp>
#include <3ds/services/hid.h>
#include "UI/Canvas.hpp"
#include "UI/Window.hpp"
namespace luib {
    void Window::onDraw(Canvas &canvas) const
    {
        Container::onDraw(canvas);
        canvas.rectangle(_aabb.x, _aabb.y, _aabb.w, topBarHeight, 0x0000FFFF);
        canvas.rectangle(_aabb.x + _aabb.w - topBarHeight, _aabb.y, topBarHeight, topBarHeight, 0x00FF00FF);
    }

    Window::Window(int x, int y, int w, int h,u32 bgColor) :
            Container(x, y, w, h,bgColor)
    {
        Element::_bringToFrontOnFocus = true;
    }

    void Window::onClick()
    {
        if(titleBarAABB().contains(touch.px,touch.py))
        {
            touchOffset.px = touch.px- _aabb.x;
            touchOffset.py = touch.py- _aabb.y;
            isGrabbed = true;
        }
        else if (closeButtonAABB().contains(touch.px,touch.py))
        {
            bgColor^=0xFF000000;
            _upper->detach(this);
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
            moveTo((7*(touch.px-touchOffset.px)+ _aabb.x)/8,
                    (7*(touch.py-touchOffset.py)+ _aabb.y)/8);
        }
    }
    Rectangle Window::titleBarAABB()
    {
        return Rectangle(_aabb.x , _aabb.y, _aabb.w - topBarHeight, topBarHeight);
    }

    Rectangle Window::closeButtonAABB()
    {
        return Rectangle(_aabb.x + _aabb.w - topBarHeight, _aabb.y, topBarHeight, topBarHeight);
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