//
// Created by Lectem on 14/04/2015.
//
#include <3ds.h>
#include <UI/Layouts/RelativeLayout.hpp>
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
    RelativeLayout topScreenLayout(0,0,400,240);
    RelativeLayout bottomScreenLayout(0,0,320,240);

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

    void update()
    {
        updateInputs();
        bottomScreenLayout.update();
        if(bottomScreenLayout.isTouched())bottomScreenLayout.onClick();
        bottomScreenLayout.draw();
        //TODO
        //topScreenLayout.draw();
    }
}