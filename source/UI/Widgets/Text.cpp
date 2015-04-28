//
// Created by Lectem on 14/04/2015.
//

#include <luib.hpp>
#include "UI/Widgets/Text.hpp"
#include <UI/Draw.hpp>
namespace luib{

    void Text::onDraw() const
    {
        int cur_x= aabb.x+1;
        int cur_y= aabb.y+1;
        int wordWidth=0;
        int wordLength=0;
        Element::onDraw();
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
                if ( wordWidth + fontPadding*2 < aabb.w
                     && cur_x + wordWidth >= aabb.getRight() )
                {
                    cur_x = aabb.x + 1;
                    cur_y += 9;
                }
                for(int wordChar=0;wordChar<wordLength;++wordChar)
                {
                    int charWidth = getCharWidth(str[wordChar]);
                    if(cur_x + charWidth > aabb.getRight())
                    {
                        if(charWidth+fontPadding*2 >= aabb.w )wordChar++;
                        cur_x = aabb.x + 1;
                        cur_y += 9;
                    }
                    if(cur_y+8 >= aabb.getBottom()) return;
                    draw::character(str[wordChar], cur_x, cur_y);
                    cur_x+=charWidth;
                }
                str+=wordLength;
            }
            else
            {
                switch (c)
                {
                    case '\n':
                    cur_x = aabb.x + 1;
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

    Text::Text(int x, int y, int w, int h,std::string text) :
            Element(x, y, w, h),
            text(text)
    {

    }

    void Text::onClick()
    {
        Element::onClick();
        printf("Text clicked\n");
    }


    int Text::getCharWidth(char c)
    {
        return 8;
    }

    int Text::getWordWidth(const char * str,int &nbCharacters)
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