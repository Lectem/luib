#include <stdio.h>
#include "Structures.hpp"

/**
 *@file Structures.cpp
 *@author Lectem
 *@date 26/04/2015
 */

namespace luib {
    int Rectangle::getLeft() const
    {
        return x;
    }

    int Rectangle::getRight() const
    {
        return x + w;
    }

    int Rectangle::getTop() const
    {
        return y;
    }

    int Rectangle::getBottom() const
    {
        return y + h;
    }

    void Rectangle::setLeft(int left)
    {
        x=left;
    }
    void Rectangle::setRight(int right)
    {
        w = right-x;
    }
    void Rectangle::setTop(int top)
    {
        x=top;
    }
    void Rectangle::setBottom(int bottom)
    {
        h = bottom - y;
    }


    bool Rectangle::contains(int const px, int const py) const
    {
        int rx = px - x, ry = py - y;
        return rx >= 0 && rx < w && ry >= 0 && ry < h;
    }


    void Padding::setValue(int value, Position pos)
    {
        switch (pos)
        {
            case LEFT:
                left = value;
                break;
            case TOP:
                top = value;
                break;
            case RIGHT:
                right = value;
                break;
            case BOTTOM:
                bot = value;
                break;
            case VERTICAL:
                top = value;
                bot = value;
                break;
            case HORIZONTAL:
                left = value;
                right = value;
                break;
            case ALL:
                top = value;
                bot = value;
                left = value;
                right = value;
                break;
        }
    }

    sizeConstraint::sizeConstraint(int value)
            : value(value)
    {
    }

    void Rectangle::setCoordinates(int const left, int const top, int const right, int const bottom)
    {
        x = left;
        y = top;
        w = right - left;
        h = bottom - top;
    }

    void Rectangle::clip(const Rectangle &clipArea)
    {
        int diff;
        if (getLeft() > clipArea.getRight() || clipArea.getLeft() > getRight())w = 0;
        else
        {
            diff = clipArea.x - x;
            if (diff > 0)
            {
                w -= diff;
                x = clipArea.x;
            }
            if (getRight() > clipArea.getRight())setRight(clipArea.getRight());

        }
        if (getTop() > clipArea.getBottom() || clipArea.getTop() > getBottom())h = 0;
        {
            diff = clipArea.y - y;
            if (diff > 0)
            {
                h -= diff;
                y = clipArea.y;
            }
            if (getBottom() > clipArea.getBottom())setBottom(clipArea.getBottom());
        }
    }
}