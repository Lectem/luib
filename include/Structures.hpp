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

        Point() : x(0),y(0) { }

        Point(int x, int y)
                : x(x), y(y) { }
        Point & operator += (Point const & rp);
        Point & operator -= (Point const & rp);
    };

    using Size = Point;

    struct Rectangle
    {
        int x, y;
        int w, h;

        Rectangle(int x=0, int y=0, int w=0, int h=0)
                : x(x), y(y), w(w), h(h) { }

        void setCoordinates(int const left,int const top,int const right,int const bottom);
        int getLeft() const;
        int getRight() const;
        int getTop() const;
        int getBottom() const;

        void setLeft(int left);
        void setRight(int right);
        void setTop(int top);
        void setBottom(int bottom);
        
        void clip(Rectangle const & clipArea);
        Point clipAndGetOffset(Rectangle const & clipArea);

        friend Rectangle operator+(const Rectangle &r,const Point p)
        {
            Rectangle res = r;
            res.x+=p.x;
            res.y+=p.y;
            return res;
        }

        friend bool operator==(const Rectangle & rl,const Rectangle & rr)
        {
            return rl.x==rr.x && rl.y == rr.y && rl.w==rr.w && rl.h == rr.h;
        }
        friend bool operator!=(const Rectangle & rl,const Rectangle & rr)
        {
            return !(rl==rr);
        }

        bool contains(const Point & point) const;
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

    struct sizeConstraint
    {
        enum ConstraintType {
            AT_MOST,
            EXACTLY,
            NOT_SPECIFIED
        };
        int value : (sizeof(int)*8-2);
        ConstraintType type: 2;
        sizeConstraint(int value);

        sizeConstraint(int value, const ConstraintType &type) : value(value), type(type)
        { }
    };
}