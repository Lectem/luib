//
// Created by Lectem on 14/04/2015.
//
#include <3ds.h>
#include "luib.hpp"


extern "C"
{

extern const struct
{
    unsigned int width;
    unsigned int height;
    unsigned int bytes_per_pixel;
    /* 2:RGB16, 3:RGB, 4:RGBA */
    unsigned char pixel_data[8 * 1024 * 4 + 1];
} fontData;
}

namespace luib{
    touchPosition touch;
    u32 kDown =0;
    u32 kUp =0;
    u32 kHeld =0;
    sf2d_texture * font;

    void Init()
    {
        font = sf2d_create_texture(8,1024,GPU_RGBA8,SF2D_PLACE_VRAM);
        sf2d_fill_texture_from_RGBA8(font, fontData.pixel_data, fontData.width, fontData.height);
        sf2d_texture_tile32(font);
    }

    void updateInputs()
    {
        hidScanInput();
        hidTouchRead(&touch);
        kDown=keysDown();
        kUp=keysUp();
        kHeld=keysHeld();
    }
}