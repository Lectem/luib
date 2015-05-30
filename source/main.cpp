#include <3ds.h>
#include <stdio.h>
#include <sf2d.h>
#include "UI/Widgets/TextArea.hpp"
#include <UI/Window.hpp>
#include <UI/Widgets/Button.hpp>
#include <UI/Layouts/RelativeLayout.hpp>
#include <stdlib.h>
#include "UI/Layouts/ScrollLayout.h"
#include "UI/Layouts/LinearLayout.hpp"
#include "luib.hpp"

using namespace luib;

int main(int argc, char **argv)
{
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0x00));
    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, 0);

    luib::Init();

    printf("\nHello World!");
    printf("Press Start to exit.\n");

    ScrollLayout_shared_ptr scrollLayout;
    if (luib::bottomScreenLayout)
    {
        luib::bottomScreenLayout->setBgColor(RGBA8(0x55,0x55,0x55,0xFFF));

        //We use layout parameters.
        //Ask for a width of 80 and to match the parent's height
        Container_shared_ptr container = luib::bottomScreenLayout->add<Container>(LayoutParams(80,LayoutParams::MATCH_PARENT));
        container->setBgColor(RGBA8(0,0x5F,0x44,0xFF));

        //Since the bottomScreenLayout is a RelativeLayout, we can ask for precise coordinates
        scrollLayout= luib::bottomScreenLayout->add<ScrollLayout>(100,20,150,150,RGBA8(0xD5,0x5D,0x42,0xff));
        auto someText = scrollLayout->add<TextArea>(10, 30, 45, 50,
                                "abcdefghijklmnopqrstuvxyz"
                                "\n0123456789"
                                "This text is scrolling!\n\n"
                                "Click the yellow button to create a window.\n\n"
                                "Click the red button to clear the console.");
        someText->setBgColor(0xAA0000FF);

        Button_shared_ptr clearButton = luib::bottomScreenLayout->add<Button>(0,0,10,10);

        //Use lambda for events !
        clearButton->setOnClickListener([](Element&){consoleClear();});
        clearButton->setBgColor(0xFF0000FF);

        auto button = make_elem<Button>(0, 230, 10, 10);
        button->setOnClickListener(
                [](Element&) {
                     auto newWindow = luib::bottomScreenLayout->add<Window>(
                                   rand() % 300, rand() % 220,
                                   rand() % 100 + 8, rand() % 200 + 8,
                                   RGBA8(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF, rand() & 0xFF));

                     newWindow->add<TextArea>(2, 2, 250, 250,"This window was created using the button.");
                });
        button->setBgColor(0xFFFF00FF);
        luib::bottomScreenLayout->attach(button);

        printf("Detaching button...\n");
        luib::bottomScreenLayout->detach(button);
        printf("Button detached\n");

        printf("Reattaching button\n");
        luib::bottomScreenLayout->attach(button);
        printf("Clearing button shared ptr...\n");
        button.reset();
        printf("It's fine since the layout now onws the button.\n");

        Window_shared_ptr w = luib::bottomScreenLayout->add<Window>(35, 150, 80, 80);
        Text_shared_ptr wText = w->add<TextArea>(2, 2, 250, 250, "This is a test window with text.");
        wText->setBgColor(RGBA8(0xFF,0xFF,0xFF,0xFF));
    }
    else
    {
        printf("bottomLayout not allocated\n");
    }

    int frame = 0;
    // Main loop
    while (aptMainLoop())
    {
        if (luib::kDown & KEY_START) break; // break in order to return to hbmenu

        scrollLayout->setScrollPos({0,-frame%scrollLayout->getHeight()});

        sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

        //Update the input, positions and render the UI
        luib::Update();

        //printf("\x1b[0;0H%f\n",sf2d_get_fps());

        sf2d_end_frame();
        sf2d_swapbuffers();
        frame++;
    }

    sf2d_fini();
    luib::Exit();
    return 0;
}