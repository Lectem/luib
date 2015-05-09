/**
 *@file ScrollLayout.cpp
 *@author Lectem
 *@date 07/05/2015
 */
#include "Structures.hpp"
#include "UI/Element.hpp"
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
        //TODO
        return Container::findFocusedElement(currentFocus, touchEvent);
    }
}