#pragma once


#include <vector>
#include "../Recangle.hpp"

class Element
{
    Rectangle AABB;
    Element* upper;
};