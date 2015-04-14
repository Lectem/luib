//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include <3ds/services/hid.h>

namespace luib {
    void updateInputs();
    extern touchPosition touch;
    extern u32 kDown;
    extern u32 kUp;
    extern u32 kHeld;
}
