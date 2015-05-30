//
// Created by Lectem on 14/04/2015.
//

#include <luib.hpp>
#include "UI/Widgets/TextArea.hpp"
#include "UI/Canvas.hpp"
namespace luib{

    void TextArea::onDraw(Canvas &canvas) const
    {

        int left = _margin.left;
        int top = _margin.top;
        int right = getWidth()-_margin.right;
        int bot = getHeight() - _margin.bot;
        int cur_x= left+1;
        int cur_y= top+1;

        int wordWidth=0;
        int wordLength=0;

        Element::onDraw(canvas);

        char const * str = text.c_str();
        while(*str)
        {
            char c = *str;
            //Printable characters ranges from 32 (' ') to 126 (~)
            //but we want to treat the space as a special case
            if(' ' < c && c <= '~')
            {
                wordWidth = getWordWidth(str,wordLength);

                //Check if the word fits on one line
                //if it does, check if we have to go to a new line
                if ( wordWidth + fontPadding*2 < right
                     && cur_x + wordWidth >= right )
                {
                    cur_x =  + 1;
                    cur_y += 9;
                }
                for(int wordChar=0;wordChar<wordLength;++wordChar)
                {
                    int charWidth = getCharWidth(str[wordChar]);
                    if(cur_x + charWidth > right)
                    {
                        if(charWidth+fontPadding*2 >= right )wordChar++;
                        cur_x = left;
                        cur_y += 9;
                    }
                    if(cur_y+8 >= bot) return;
                    canvas.character(str[wordChar], cur_x, cur_y);
                    cur_x+=charWidth;
                }
                str+=wordLength;
            }
            else
            {
                switch (c)
                {
                    case '\n':
                    cur_x = left;
                    cur_y += 9;
                        break;
                    case ' ':
                        cur_x += getCharWidth(' ');
                        break;
                    default:
                        printf("unrecognized character : %c",c);
                        break;
                }
                ++str;
            }
        }
    }

    TextArea::TextArea(int x, int y, int w, int h,std::string text) :
            Element(x, y, w, h),
            text(text)
    {
    }

    void TextArea::onTouchEvent(const TouchEvent &touchEvent)
    {
        Element::onTouchEvent(touchEvent);
        printf("TextArea clicked\n");
    }


    int TextArea::getCharWidth(char c)
    {
        return 8;
    }

    int TextArea::getWordWidth(const char * str,int &nbCharacters)
    {
        int width =0;
        nbCharacters=0;
        while(*str && *str != '\n' && *str!= ' ' && *str != '\t')
        {
            width+=getCharWidth(*str)+fontPadding;
            nbCharacters++;
            str++;
        }
        return width;
    }

}