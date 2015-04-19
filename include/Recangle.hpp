//
// Created by Lectem on 14/04/2015.
//

#pragma once
namespace luib {
    struct Rectangle
    {
        int x, y;
        int w, h;

        Rectangle() { }
        Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }

        bool contains(int const px, int const py) const
        {
            int rx= px-x,ry=py-y;
            return rx >=0 && rx < w && ry >=0 && ry < h;
        }
    };


}