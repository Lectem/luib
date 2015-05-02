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
    RelativeLayout_shared_ptr topScreenLayout;
    RelativeLayout_shared_ptr bottomScreenLayout;
    Element* elementWithFocus = nullptr;
    Canvas topCanvas;
    Canvas bottomCanvas;

    void findFocus();

    void Init()
    {
        topScreenLayout= make_elem<RelativeLayout>(0,0,400,240);
        bottomScreenLayout= make_elem<RelativeLayout>(0,0,320,240);
        elementWithFocus = bottomScreenLayout.get();
        font = sf2d_create_texture(8,1024,GPU_RGBA8,SF2D_PLACE_RAM);
        sf2d_fill_texture_from_RGBA8(font, fontData.pixel_data, fontData.width, fontData.height);
        sf2d_texture_tile32(font);
    }

    void Exit()
    {
        topScreenLayout.reset();
        bottomScreenLayout.reset();
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

            bottomScreenLayout->measure(sizeConstraint{320,sizeConstraint::EXACTLY},
                                        sizeConstraint{240,sizeConstraint::EXACTLY});
            bottomScreenLayout->layout(Rectangle{0,0,320,240});
            bottomScreenLayout->update();
            if(kDown&KEY_TOUCH)
            {
                //Update focus only on new click
                findFocus();
                if(elementWithFocus != nullptr)
                {
                    elementWithFocus->onClick();
                }
                //Check again, in case the element has lost focus or was destroyed...
                if(elementWithFocus != nullptr)
                {
                    elementWithFocus->onFocus();
                }
            }
            if (kHeld&KEY_TOUCH)
            {
                if(elementWithFocus != nullptr)
                {
                    elementWithFocus->onHold();
                }
                //Check again, in case the element has lost focus or was destroyed...
                if(elementWithFocus != nullptr)
                {
                    elementWithFocus->onFocus();
                }
            }
            if(kUp&KEY_TOUCH)
            {
                ResetFocus();
            }
            if(elementWithFocus)elementWithFocus->bringToFront();
            bottomScreenLayout->draw(bottomCanvas);
        }
        //TODO
        //topScreenLayout.draw(topCanvas);
    }

    void ResetFocus()
    {
        if(elementWithFocus != nullptr)
        {
            elementWithFocus->_hasFocus = false;
            elementWithFocus->onFocusLoss();
        }
        elementWithFocus = bottomScreenLayout.get();
    }

    void findFocus()
    {
        bottomScreenLayout->getFocusedElement(elementWithFocus);
    }
}