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

    void Window::onTouchEvent(const TouchEvent &touchEvent)
    {
        switch(touchEvent.type)
        {
            case TouchEvent::DOWN:
                printf("Window: touchEvent DOWN\n");
                if (titleBarAABB().contains(touchEvent.viewPos))
                {
                    isGrabbed = true;
                    printf("Window title bar clicked\n");
                }
                else if (closeButtonAABB().contains(touchEvent.viewPos))
                {
                    bgColor ^= 0xFF000000;
                    detachFromParent();
                    printf("Window close button clicked\n");
                }
                else
                {
                    printf("Window clicked\n");
                    Container::onTouchEvent(touchEvent);
                }
                break;
            case TouchEvent::MOTION :
                if(isGrabbed)
                {
                    move(touchEvent.deltaPos.x,touchEvent.deltaPos.y);
                }
                break;
            case TouchEvent::UP:break;
                isGrabbed = false;
            default:break;
        }
    }


    Rectangle Window::titleBarAABB() const
    {
        return Rectangle(_margin.left , _margin.top, getWidth() - (topBarHeight+_margin.right), topBarHeight);
    }

    Rectangle Window::closeButtonAABB() const
    {
        return Rectangle(_margin.left + getWidth() - (topBarHeight+_margin.right), _margin.top,
                         topBarHeight, topBarHeight);
    }

    void Window::onFocus()
    {

    }

    void Window::onFocusLoss()
    {
        isGrabbed = false;
        printf("Window lost focus\n");
    }

    void Window::bringToFront(Element *element)
    {
        Container::bringToFront(element);
        Element::bringToFront();
    }


    void Window::onLayout(Rectangle const &coordinates)
    {
        for(auto& childPtr:children)
        {
            childPtr->layout(Rectangle{0,topBarHeight,getWidth(),getHeight()-topBarHeight});
        }
    }
}