/**
 *@file ScrollLayout.cpp
 *@author Lectem
 *@date 07/05/2015
 */
#include "Structures.hpp"
#include "UI/Layouts/ScrollLayout.h"


namespace luib {

    ScrollLayout::ScrollLayout(int x, int y, int w, int h, u32 bgColor) :
            Container(x, y, w, h, bgColor),
            scrollPos(0,0)
    {
    }

    void ScrollLayout::onDraw(Canvas &canvas) const
    {
        canvas.moveOrigin(-scrollPos);
        Container::onDraw(canvas);
        canvas.moveOrigin(scrollPos);
    }

    bool ScrollLayout::findFocusedElement(Element *&currentFocus, TouchEvent &touchEvent)
    {
        //TODO:finish?
        for(int child = _children.size()-1;child>=0;--child)
        {
            Point relativeSytlusPos = touchEvent.viewPos;
            Rectangle& childAABB = getChildAABB(_children[child].get());
            relativeSytlusPos.x -= childAABB.x;
            relativeSytlusPos.y -= childAABB.y;
            relativeSytlusPos-= scrollPos;
            TouchEvent dispatchedTouchEvent = touchEvent;
            dispatchedTouchEvent.viewPos = relativeSytlusPos;
            if (childAABB.contains(touchEvent.viewPos+scrollPos) &&
                _children[child]->findFocusedElement(currentFocus, dispatchedTouchEvent))
            {
                touchEvent = dispatchedTouchEvent;
                return true;
            }
        }
        return Element::findFocusedElement(currentFocus, touchEvent);
    }
}