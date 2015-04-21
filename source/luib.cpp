//
// Created by Lectem on 14/04/2015.
//
#include <3ds.h>
#include <UI/Layouts/RelativeLayout.hpp>
#include "luib.hpp"


#include "fontData.hcc"

namespace luib{
    touchPosition touch;
    u32 kDown =0;
    u32 kUp =0;
    u32 kHeld =0;
    sf2d_texture * font = nullptr;
    RelativeLayout* topScreenLayout = nullptr;
    RelativeLayout* bottomScreenLayout = nullptr;
    Element* elementWithFocus = nullptr;

    void findFocus();

    void Init()
    {
        topScreenLayout= new RelativeLayout(0,0,400,240);
        bottomScreenLayout=new RelativeLayout(0,0,320,240);
        elementWithFocus = bottomScreenLayout;
        font = sf2d_create_texture(8,1024,GPU_RGBA8,SF2D_PLACE_RAM);
        sf2d_fill_texture_from_RGBA8(font, fontData.pixel_data, fontData.width, fontData.height);
        sf2d_texture_tile32(font);
    }

    void Exit()
    {
        delete topScreenLayout; topScreenLayout = nullptr;
        delete bottomScreenLayout; bottomScreenLayout = nullptr;
    }

    void UpdateInputs()
    {
        hidScanInput();
        hidTouchRead(&touch);
        kDown=keysDown();
        kUp=keysUp();
        kHeld=keysHeld();
    }

    void Update()
    {
        UpdateInputs();
        if(bottomScreenLayout)
        {
            bottomScreenLayout->update();
            if (kDown&KEY_TOUCH || kHeld&KEY_TOUCH)
            {
                findFocus();
                if(elementWithFocus != nullptr)
                {
                    elementWithFocus->onFocus();
                    if(kDown&KEY_TOUCH)
                    {
                        elementWithFocus->onClick();
                    }
                    if(kHeld&KEY_TOUCH)
                    {
                        elementWithFocus->onHold();
                    }
                }
            }
            if(kUp&KEY_TOUCH)
            {
                ResetFocus();
            }
            bottomScreenLayout->draw();
        }
        //TODO
        //topScreenLayout.draw();
    }

    void ResetFocus()
    {
        if(elementWithFocus != nullptr)
        {
            elementWithFocus->hasFocus = false;
            elementWithFocus->onFocusLoss();
        }
        elementWithFocus = bottomScreenLayout;
    }

    void findFocus()
    {
        bottomScreenLayout->getFocusedElement(elementWithFocus);
    }
}