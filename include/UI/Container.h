//
// Created by Lectem on 14/04/2015.
//
#pragma once
#include "Element.hpp"

class Container :public Element
{
    std::vector<Element *> children;
};

