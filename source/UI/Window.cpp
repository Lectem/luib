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

    Window::Window(int x, int y, int w, int h,u32 bgColor) : Container(x, y, w, h,bgColor)
    {

    }

    void Window::onClick()
    {
        if(titleBarAABB().contains(touch.px,touch.py))
        {
            lastTouchPos = touch;
            isGrabbed = true;
        }
        else if (closeButtonAABB().contains(touch.px,touch.py))
        {
            bgColor^=0xFF000000;
            upper->detach(this);
        }
        else
        {
            Container::onClick();
        }
    }

    void Window::onHold()
    {
        printf("Window::OnClick\n");
        if(isGrabbed)
        {
            printf("delta (%d,%d)\n",touch.px - lastTouchPos.px,touch.py - lastTouchPos.py);
            aabb.x+=touch.px - lastTouchPos.px;
            aabb.y+=touch.py - lastTouchPos.py;
            printf("newpos (%d %d)\n",aabb.x,aabb.y);
            lastTouchPos = touch;
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
        printf("Window focused\n");
    }

    void Window::onFocusLoss()
    {
        isGrabbed = false;
        printf("Window focus lost\n");
    }

}