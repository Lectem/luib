//
// Created by Lectem on 19/04/2015.
//
#pragma once

/**
 * Abastraction level of sf2dlib
 */

#include <sf2d.h>
#include "Structures.hpp"

namespace luib {

    class Canvas
    {
    public:


        Canvas(Point const &origin = {0,0}) :
                _origin(origin),
                _frame({0,0,1024,1024}){ }


        /**
         * @brief Draws a rectangle
         * @param x x coordinate of the top left corner of the rectangle
         * @param y y coordinate of the top left corner of the rectangle
         * @param w rectangle width
         * @param w rectangle height
         * @param color the color to draw the rectangle
         */
        void rectangle(Rectangle rectangle,const u32 color);
        void rectangle(const int x, const int y, const int w, const int h, const u32 color);


        /**
         * @brief Draws a part of a texture
         * @param texture the texture to draw
         * @param x the x coordinate to draw the texture to
         * @param y the y coordinate to draw the texture to
         * @param tex_x the starting point (x coordinate) where to start drawing
         * @param tex_y the starting point (y coordinate) where to start drawing
         * @param tex_w the width to draw from the starting point
         * @param tex_h the height to draw from the starting point
         */
        void texture_part(const sf2d_texture *texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h);
        void texture_part(const sf2d_texture *texture,Rectangle dst, Point texOffset);

        /**
         * @brief Draws a single character
         * @param c the character to draw
         * @param x the x coordinate to draw the texture to
         * @param y the y coordinate to draw the texture to
         */
        void character(const char c,const int x,const int y);

        void setOrigin(Point const &origin);
        void setOrigin(int const x, int const y);
        Point getOrigin() const;

        Rectangle getFrame() const;
        void setFrame(const Rectangle &frame);
        void setFrameAndOrigin(const Rectangle &frame);

    private:
        Point _origin;
        Rectangle _frame;
    };

}