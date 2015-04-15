#pragma once

#include <sf2d.h>
#include <vector>
#include "Recangle.hpp"

namespace luib {
    class Element
    {
    public:
        Element(int x =0 ,int y = 0,int w = 1,int h = 1):
                bgColor(RGBA8(0xFF,0,0,0xFF)),
                aabb{x,y,w,h}
        {
            upper=NULL;
            screen=GFX_BOTTOM;
        }
        virtual ~Element(){}
        virtual void draw();
        virtual bool isTouched();
        u32 bgColor;
    protected:
        Rectangle aabb;
        Element *upper;
        gfxScreen_t screen;
    };

}