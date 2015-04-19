#pragma once

#include <sf2d.h>
#include <vector>
#include <stdio.h>
#include "Recangle.hpp"

namespace luib {
    class Element
    {
    friend class Container;
    public:
        Element(int x =0 ,int y = 0,int w = 1,int h = 1):
                bgColor(RGBA8(0xFF,0,0,0xFF)),
                aabb{x,y,w,h}
        {
            screen=GFX_BOTTOM;
            printf("Element created\n");
        }
        virtual ~Element(){}
        virtual void draw() const;
        virtual bool isTouched();
        virtual void onClick();
        u32 bgColor;
    protected:
        Rectangle aabb;
        Element *upper = nullptr;
        Element *root = nullptr;
        gfxScreen_t screen;
    };

}