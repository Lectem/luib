#include "Structures.hpp"

/**
 *@file Structures.cpp
 *@author Lectem
 *@date 26/04/2015
 */


int luib::Rectangle::getLeft() const
{
    return x;
}

int luib::Rectangle::getRight() const
{
    return x + w;
}

int luib::Rectangle::getTop() const
{
    return y;
}

int luib::Rectangle::getBottom() const
{
    return y + h;
}

bool luib::Rectangle::contains(int const px, int const py) const
{
    int rx = px - x, ry = py - y;
    return rx >= 0 && rx < w && ry >= 0 && ry < h;
}


void luib::Padding::setValue(int value, Position pos)
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

luib::sizeConstraint::sizeConstraint(int value)
        :value(value)
{

}
