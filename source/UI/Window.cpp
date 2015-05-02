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
        canvas.rectangle(titleBarAABB(), 0x0000FFFF);
        canvas.rectangle(closeButtonAABB(), 0x00FF00FF);
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
            touchOffset.px = touch.px- _margin.left;
            touchOffset.py = touch.py- _margin.top;
            isGrabbed = true;
        }
        else if (closeButtonAABB().contains(touch.px,touch.py))
        {
            bgColor^=0xFF000000;
            detachFromParent();
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
            moveTo((7*(touch.px-touchOffset.px)+ _margin.left)/8,
                    (7*(touch.py-touchOffset.py)+_margin.top)/8);
        }
    }
    Rectangle Window::titleBarAABB() const
    {
        return Rectangle(_margin.left , _margin.top, getWidth() - topBarHeight, topBarHeight);
    }

    Rectangle Window::closeButtonAABB() const
    {
        return Rectangle(_margin.left + getWidth() - topBarHeight, getHeight(), topBarHeight, topBarHeight);
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