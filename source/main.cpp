#include <3ds.h>
#include <stdio.h>
#include <sf2d.h>
#include <UI/Widgets/Text.hpp>
#include <UI/Window.hpp>
#include <UI/Widgets/Button.hpp>
#include <UI/Layouts/RelativeLayout.hpp>
#include "UI/Layouts/LinearLayout.hpp"
#include "luib.hpp"


int main(int argc, char **argv)
{
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, 0);

    luib::Init();

    printf("Hello World!");
    printf("Press Start to exit.\n");

    if(luib::bottomScreenLayout)
    {
        luib::Text_shared_ptr someText = luib::bottomScreenLayout->add<luib::Text>(55, 20, 250, 250,
                                                                                   "abcdefghijklmnopqrstuvxyz\n0123456789");
        someText->bgColor = 0x000000FF;

        luib::Button_shared_ptr button = luib::make_elem<luib::Button>(0, 230, 10, 10);
        button->bgColor = 0xFFFF00FF;
        luib::bottomScreenLayout->attach(button);
        printf("Detaching button...\n");
        luib::bottomScreenLayout->detach(button);
        printf("Button detached\n");
        printf("Reattaching button\n");
    luib::bottomScreenLayout->attach(button);
    printf("Clearing button shared ptr...\n");
    button.reset();
    luib::Window_shared_ptr w = luib::bottomScreenLayout->add<luib::Window>(35, 150, 80, 80);


    }
    else
    {
        printf("bottomLayout not allocated\n");
    }
    int frame=0;
    // Main loop
    while (aptMainLoop())
    {
        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)


        if (luib::kDown & KEY_START) break; // break in order to return to hbmenu

        // Flush and swap framebuffers

        sf2d_start_frame(GFX_BOTTOM,GFX_LEFT);

        luib::update();

        sf2d_end_frame();

        sf2d_swapbuffers();

        //Wait for VBlank
        gspWaitForVBlank();
        frame++;
    }

    sf2d_fini();
    luib::Exit();
    return 0;
}
