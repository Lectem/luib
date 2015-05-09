#pragma once

#include <sf2d.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "utils.hpp"
#include "Structures.hpp"
#include "Canvas.hpp"
#include "Inputs.h"

namespace luib {

    struct LayoutParams{
        enum :int{DEFAULT=-3,WRAP_CONTENT=-2, MATCH_PARENT=-1};
        LayoutParams(int width=DEFAULT, int height=DEFAULT) : width(width), height(height) { }
        int width;
        int height;
    };

    class Container;
    class Element
    {
        enum VISIBILITY{
            VISIBLE,    //!<default, the view will be visible and drawn
            INVISIBLE,  //!<The view will take the same space as if it was visible, but will not be drawn
            GONE        //!<The container will consider that this element takes no space and won't draw it
        };

        friend class Container;
        friend void Update();
        friend void ResetFocus();
        friend void dispatchTouchEvent(TouchEvent touchEvent);
    public:
        Element(LayoutParams layoutParams){_layoutParams=layoutParams;}
        Element(int x =0,int y=0,int w = 1,int h = 1,u32 bgColor = 0):
                bgColor(bgColor),
                _aabb{x,y,w,h},
                _layoutParams{w,h}
        {
            _screen =GFX_BOTTOM;
        }
        virtual ~Element();

        //Do not overload/ride. Override onMeasure instead
        void measure(sizeConstraint width, sizeConstraint height);

        Size getMeasuredSize() const;
        void setMeasuredSize(const Size measuredSize);
        void setMeasuredSize(const int width,const int height);

        //Do not overload/ride. Override onLayout instead
        void layout(Rectangle const & coordinates);
        void requestLayout();
        //same as requestLayout but doesn't call requestLayout on parent
        void forceLayout();

        int getWidth() const;
        int getHeight() const;

        //Do not overload/ride. Override onDraw instead
        void draw(Canvas &canvas) const;

        virtual bool isTouched();
        virtual void move(int x,int y);
        virtual void moveTo(int x,int y);

        void detachFromParent();


        void setBgColor(u32 bgColor);

        u32 bgColor;


    protected:
        void drawBG(Canvas &canvas) const;

        virtual void onMeasure(sizeConstraint width, sizeConstraint height);
        virtual void onLayout(Rectangle const &coordinates){}
        virtual void onDraw(Canvas &canvas) const{};
        virtual void onDrawScrollBars(Canvas &canvas) const{};
        virtual void onSizeChanged(){};
        virtual void onTouchEvent(const TouchEvent &touchEvent);
        virtual void onFocus(){}
        virtual void onFocusLoss(){}

        const LayoutParams getLayoutParams() const { return _layoutParams; }
        int defaultSize(int minSize,int layoutsize, sizeConstraint constraint);

        void bringToFront();

        Margin _margin;
        bool _bringToFrontOnFocus = false;


    private:


        /**
         * This method has to change currentFocus and touchEvent according to the focused element
         * Internal usage only.
         */
        virtual bool findFocusedElement(Element *&currentFocus, TouchEvent &touchEvent);

        Container *_upper = nullptr;
        Container *_root = nullptr;

        /**
         * AABB stands for aligned axis bounding box
         * It represents the rectangle allocated to the view by the parent
         * It is relative to the parent origin and should only be used internally for layout purposes
         */
        Rectangle _aabb;
        Size _measuredSize;

        int _depthLevel = 0;
        bool _isLayoutNeeded = true;
        bool _hasFocus = false;
        gfxScreen_t _screen;
        VISIBILITY _visibility;
        LayoutParams _layoutParams;

    };

    using Element_shared_ptr = std::shared_ptr<Element>;


    template <class T,class ... Args>
    std::shared_ptr<T> make_elem(Args && ... args)
    {
        Derived_from<T,Element>();//Error if T does not derive from Element
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}