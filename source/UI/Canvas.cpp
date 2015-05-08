//
// Created by Lectem on 19/04/2015.
//
#include "UI/Canvas.hpp"

#include <sf2d.h>
#include <luib.hpp>

namespace luib {

    void Canvas::setOrigin(Point const &origin)
    {
        _origin =origin;
    }

    void Canvas::setOrigin(int const x, int const y)
    {
        _origin.x=x;
        _origin.y=y;
    }


    Point &Canvas::getOrigin()
    {
        return _origin;
    }

    const Point &Canvas::getOrigin() const
    {
        return _origin;
    }

    void Canvas::rectangle(Rectangle rectangle,const u32 color)
    {
        rectangle.x+=_origin.x;
        rectangle.y+=_origin.y;
        rectangle.clip(_frame);
        //Don't issue a draw call if nothing is to be displayed...
        if(rectangle.w>0 && rectangle.h>0)
        {
            sf2d_draw_rectangle(rectangle.x,rectangle.y,
                                rectangle.w,rectangle.h,color);
        }
    }
    void Canvas::rectangle(const int x,const int y,const int w,const int h,const u32 color)
    {
        rectangle(Rectangle{x,y+y, w,h},
                color);
    }

    void Canvas::texture_part(const sf2d_texture *texture,Rectangle dst,Point texOffset)
    {
        dst.x+=_origin.x;
        dst.y+=_origin.y;
        texOffset+=dst.clipAndGetOffset(_frame);
        //Don't issue a draw call if nothing is to be displayed...
        if(dst.w >0 && dst.h>0)
        {
            sf2d_draw_texture_part(texture,dst.x,dst.y,texOffset.x,texOffset.y,dst.w,dst.h);
        }
    }
    void Canvas::texture_part(const sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
    {
        texture_part(texture,Rectangle{x,y,tex_w,tex_h},Point{tex_x,tex_y});
    }

    void Canvas::character(const char c, const int x, const int y)
    {
        texture_part(font, x, y,
                             0, (c-32) * 8,
                             8, 8);
    }

    Rectangle Canvas::getFrame() const
    {
        return _frame;
    }


    void Canvas::setFrame(const Rectangle &frame)
    {
        _frame=frame;
    }

    void Canvas::setFrameAndOrigin(const Rectangle &frame)
    {
        _origin.x=frame.x;
        _origin.y=frame.y;
        _frame = frame;
    }


    void Canvas::moveOrigin(const Point &delta)
    {
        _origin+=delta;
    }

    void Canvas::moveOrigin(int dx, int dy)
    {
        _origin+={dx,dy};
    }


    void Canvas::moveFrame(const Point &delta)
    {
        _frame+=delta;
    }

    void Canvas::moveFrame(int dx, int dy)
    {
        _frame+={dx,dy};
    }

    void Canvas::clipFrame(const Rectangle &clipArea)
    {
        _frame.clip(clipArea);
    }
}