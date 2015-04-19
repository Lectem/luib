//
// Created by Lectem on 14/04/2015.
//

#include <luib.hpp>
#include "UI/Widgets/Text.hpp"
#include <UI/Draw.hpp>
namespace luib{

    void Text::draw() const
    {
        int cur_x= aabb.x+1;
        int cur_y= aabb.y+1;
        Element::draw();
        for(char c :text)
        {
            if(c >=32 && c<128)
            {
                c-=32;
                if (cur_x + 8 >= aabb.x + aabb.w )
                {
                    cur_x = aabb.x + 1;
                    cur_y += 9;
                }
                if (cur_y + 8 <= aabb.y + aabb.h)
                {
                    draw::texture_part(font, cur_x, cur_y, 0, c * 8, 8, 8);
                    cur_x += 9;
                }
            }
            else if( c == '\n')
            {
                cur_x = aabb.x + 1;
                cur_y += 9;
            }
        }
    }

    Text::Text(int x, int y, int w, int h,std::string text) :
            Element(x, y, w, h),
            text(text)
    {

    }
}