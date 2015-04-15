#include <3ds.h>
#include <stdio.h>
#include <sf2d.h>
#include <UI/Widgets/Text.hpp>
#include "UI/Layouts/LinearLayout.hpp"
#include "luib.hpp"


int main(int argc, char **argv)
{
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, 0);

    luib::Init();

    printf("\x1b[15;19HHello World!");

    printf("\x1b[29;15HPress Start to exit.");
    luib::LinearLayout linearLayout(0,0,50,50);
    luib::Text someText(55,20,250,250,"abcdefghijklmnopqrstuvxyz\n0123456789");
    someText.bgColor = 0x000000FF;


    int frame=0;
    // Main loop
    while (aptMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        luib::updateInputs();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)


        if (luib::kDown & KEY_START) break; // break in order to return to hbmenu

        // Flush and swap framebuffers

        sf2d_start_frame(GFX_BOTTOM,GFX_LEFT);
        if(linearLayout.isTouched())
        {
            linearLayout.bgColor+=20;
            printf("touched during frame %d\n",frame);
        }
        linearLayout.draw();
        someText.draw();
        sf2d_end_frame();

        sf2d_swapbuffers();

        //Wait for VBlank
        gspWaitForVBlank();
        frame++;
    }

    sf2d_fini();
    return 0;
}
