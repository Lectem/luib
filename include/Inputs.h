/**
 *@file Inputs.h
 *@author Lectem
 *@date 02/05/2015
 */
#pragma once

#include "Structures.hpp"

namespace luib {
    struct TouchEvent
    {
        enum Type
        {
            NONE,DOWN, HELD, UP, MOTION
        };
        Type type = NONE;
        Point rawPos;
        Point viewPos;
        Point deltaPos;
    };

}