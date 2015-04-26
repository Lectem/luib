//
// Created by Lectem on 14/04/2015.
//

#pragma once
namespace luib {

    enum Position
    {
        LEFT,TOP,RIGHT,BOTTOM,
        VERTICAL,HORIZONTAL,
        ALL
    };

    struct Point
    {
        int x, y;
        Point(int x=0, int y=0)
                : x(x), y(y) { }
    };

    using Size = Point;

    struct Rectangle
    {
        int x, y;
        int w, h;

        Rectangle(int x=0, int y=0, int w=0, int h=0)
                : x(x), y(y), w(w), h(h) { }

        int getLeft() const;
        int getRight() const;
        int getTop() const;
        int getBottom() const;

        bool contains(int const px, int const py) const;
    };

    struct Padding
    {
        int left, top;
        int right, bot;


        Padding(int left=0, int top=0, int right=0, int down=0) :
                left(left), top(top), right(right), bot(down)
        { }

        Padding(int value,Position pos)
            :Padding()
        {
            setValue(value,pos);
        }
        void setValue(int value, Position pos);
    };

    using Margin = Padding;
}