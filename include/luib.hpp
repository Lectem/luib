//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include <3ds.h>
#include <sf2d.h>

namespace luib {
    void Init();
    void updateInputs();
    extern touchPosition touch;
    extern u32 kDown;
    extern u32 kUp;
    extern u32 kHeld;
    extern sf2d_texture * font;
}
