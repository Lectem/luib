//
// Created by Lectem on 14/04/2015.
//
#include <3ds.h>
#include <3ds/services/hid.h>
#include "UI/Layouts/RelativeLayout.hpp"
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
    TouchEvent touchEvent;

    void dispatchTouchEvent(TouchEvent touchEvent);

    void Init()
    {
        topScreenLayout= make_elem<RelativeLayout>(0,0,400,240);
        bottomScreenLayout= make_elem<RelativeLayout>(0,0,150,240);
        elementWithFocus = bottomScreenLayout.get();
        font = sf2d_create_texture(8,1024,TEXFMT_RGBA8,SF2D_PLACE_RAM);
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
        kDown = keysDown();
        kUp = keysUp();
        kHeld = keysHeld();

        static touchPosition oldPos = touch;
        touchEvent.type = TouchEvent::NONE;
        if (kDown & KEY_TOUCH)
        {
            touchEvent.heldDuration++;
            touchEvent.type = TouchEvent::DOWN;
            touchEvent.rawPos = {touch.px, touch.py};
            touchEvent.viewPos = touchEvent.rawPos;
            oldPos=touch;
        }
        else if (kHeld & KEY_TOUCH)
        {
            touchEvent.heldDuration++;
            touchEvent.type = TouchEvent::HELD;
            if(touchEvent.heldDuration>0 && (oldPos.px != touch.px || oldPos.py != touch.py))
            {
                touchEvent.type = TouchEvent::MOTION;
                touchEvent.deltaPos.x=touch.px - oldPos.px;
                touchEvent.deltaPos.y=touch.py - oldPos.py;
            }
            oldPos=touch;
        }
        if (kUp & KEY_TOUCH)
        {
            touchEvent.heldDuration=0;
            touchEvent.type = TouchEvent::UP;
        }
    }

    static Rectangle topScreenFrame{0,0,400,240};
    static Rectangle bottomScreenFrame{0,0,320,240};

    void Update()
    {
        UpdateInputs();
        if(bottomScreenLayout)
        {
            bottomCanvas.setFrameAndOrigin(bottomScreenFrame);
            dispatchTouchEvent(touchEvent);
            //printf("Measure bottom screen...\n");
            bottomScreenLayout->measure(sizeConstraint{bottomScreenFrame.w,sizeConstraint::EXACTLY},
                                        sizeConstraint{bottomScreenFrame.h,sizeConstraint::EXACTLY});
            bottomScreenLayout->layout(bottomScreenFrame);
            bottomScreenLayout->draw(bottomCanvas);
        }
        if(topScreenLayout)
        {
            topScreenLayout->measure(sizeConstraint{400, sizeConstraint::EXACTLY},
                                     sizeConstraint{240, sizeConstraint::EXACTLY});
            topScreenLayout->layout(Rectangle{0, 0, 400, 240});
            topScreenLayout->draw(topCanvas);
        }
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

    /**
     * This function is in charge of finding the newly focused element if needed, and to dispatch the
     * TouchEvent to the focused Element.
     */
    void dispatchTouchEvent(TouchEvent touchEvent)
    {
        switch (touchEvent.type)
        {
            case TouchEvent::DOWN :
            {
                Element *oldElementWithFocus = elementWithFocus;
                elementWithFocus = bottomScreenLayout.get();
                if (bottomScreenLayout)bottomScreenLayout->findFocusedElement(elementWithFocus, touchEvent);
                if (oldElementWithFocus != nullptr && oldElementWithFocus != elementWithFocus)
                {
                    oldElementWithFocus->_hasFocus = false;
                    oldElementWithFocus->onFocusLoss();
                    elementWithFocus->_hasFocus=true;
                    elementWithFocus->onFocus();
                }
                elementWithFocus->onTouchEvent(touchEvent);
            }
                break;
            case TouchEvent::MOTION :
            case TouchEvent::HELD :
            case TouchEvent::UP :
                elementWithFocus->onTouchEvent(touchEvent);
                break;
            case TouchEvent::NONE :break;
        }
        if(elementWithFocus != nullptr)
        {
            elementWithFocus->bringToFront();
        }
    }
}