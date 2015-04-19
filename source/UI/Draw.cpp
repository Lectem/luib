//
// Created by Lectem on 19/04/2015.
//
#include "UI/Draw.hpp"

#include <sf2d.h>
namespace luib {

    void draw::rectangle(const int x,const int y,const int w,const int h,const u32 color)
    {
        sf2d_draw_rectangle(x,y,w,h,color);
    }

    void draw::texture_part(const sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
    {
        sf2d_draw_texture_part(texture,x,y,tex_x,tex_y,tex_w,tex_h);
    }

}