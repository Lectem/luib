//
// Created by Lectem on 19/04/2015.
//
#include "UI/Canvas.hpp"

#include <sf2d.h>
#include <luib.hpp>

namespace luib {

    void Canvas::rectangle(const int x,const int y,const int w,const int h,const u32 color)
    {
        sf2d_draw_rectangle(x+_position.x,y+_position.y,w,h,color);
    }

    void Canvas::texture_part(const sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
    {
        sf2d_draw_texture_part(texture,x+_position.x,y+_position.y,tex_x,tex_y,tex_w,tex_h);
    }

    void Canvas::character(const char c, const int x, const int y)
    {
        Canvas::texture_part(font, x+_position.x,y+_position.y, 0, (c-32) * 8, 8, 8);
    }

}