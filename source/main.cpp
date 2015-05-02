#include <3ds.h>
#include <stdio.h>
#include <sf2d.h>
#include <UI/Widgets/Text.hpp>
#include <UI/Window.hpp>
#include <UI/Widgets/Button.hpp>
#include <UI/Layouts/RelativeLayout.hpp>
#include <stdlib.h>
#include "UI/Layouts/LinearLayout.hpp"
#include "luib.hpp"

class MyButton:public luib::Button{
public:

    MyButton(int x, int y, int w, int h);
    virtual void onTouchEvent(const luib::TouchEvent &touchEvent) override;
};


class ClearConsoleButton:public luib::Button{
public:

    ClearConsoleButton(int x, int y, int w, int h);
    virtual void onTouchEvent(const luib::TouchEvent &touchEvent) override;
};

int main(int argc, char **argv)
{
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0x00));

    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, 0);

    luib::Init();

    printf("\nHello World!");
    printf("Press Start to exit.\n");

    if (luib::bottomScreenLayout)
    {
        luib::bottomScreenLayout->bgColor = RGBA8(0x55,0x55,0x55,0xFFF);
        luib::Text_shared_ptr someText =
                luib::bottomScreenLayout->add<luib::Text>(100, 20, 150, 150,
                                                          "abcdefghijklmnopqrstuvxyz\n0123456789");
        someText->bgColor = 0xAA0000FF;

        auto clearButton = luib::bottomScreenLayout->add<ClearConsoleButton>(0,0,10,10);
        clearButton->bgColor = 0xFF0000FF;

        auto button = luib::make_elem<MyButton>(0, 230, 10, 10);
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
        luib::Text_shared_ptr wText = w->add<luib::Text>(2, 2, 250, 250,
                                                         "This is a test window with text.");
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
        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)


        if (luib::kDown & KEY_START) break; // break in order to return to hbmenu

        // Flush and swap framebuffers

        sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

        //luib::UpdateInputs();
        luib::Update();
        printf("\x1b[0;0H%f\n",sf2d_get_fps());
        sf2d_end_frame();
        sf2d_swapbuffers();

        frame++;
    }

    sf2d_fini();
    luib::Exit();
    return 0;
}

void MyButton::onTouchEvent(const luib::TouchEvent &touchEvent)
{
    if(touchEvent.type==luib::TouchEvent::DOWN)
    {
        luib::Element::onTouchEvent(touchEvent);
        auto newWindow = luib::bottomScreenLayout->add<luib::Window>(rand() % 300, rand() % 220,
                                                                     rand() % 100 + 8, rand() % 200 + 8,
                                                                     RGBA8(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF,
                                                                           rand() & 0xFF));
        newWindow->add<luib::Text>(2, 2, 250, 250,
                                   "This is a test window with text.");
    }
}

MyButton::MyButton(int x, int y, int w, int h) : Button(x, y, w, h)
{

}

ClearConsoleButton::ClearConsoleButton(int x, int y, int w, int h) : Button(x, y, w, h)
{

}

void ClearConsoleButton::onTouchEvent(const luib::TouchEvent &touchEvent)
{
    if(touchEvent.type==luib::TouchEvent::DOWN)
        consoleClear();
}
