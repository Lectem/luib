#pragma once

#include <sf2d.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "utils.hpp"
#include "Structures.hpp"
#include "Canvas.hpp"
namespace luib {


    class Container;
    class Element
    {
    enum VISIBILITY{
        VISIBLE,    //!<default, the view will be visible and drawn
        INVISIBLE,  //!<The view will take the same space as if it was visible, but will not be drawn
        GONE        //!<The container will consider that this element takes no space and won't draw it
    };
        friend class Container;
        friend void ::luib::Update();
        friend void ::luib::ResetFocus();
        friend void ::luib::findFocus();
    public:
        Element(){}
        Element(int x ,int y,int w = 1,int h = 1,u32 bgColor = RGBA8(0,0,0,0)):
                bgColor(bgColor),
                _aabb{x,y,w,h}
        {
            _screen =GFX_BOTTOM;
        }
        virtual ~Element();
        void measure(sizeConstraint width, sizeConstraint height);
        //void layout();
        void draw(Canvas &canvas) const;
        virtual void update();
        virtual bool isTouched();
        virtual void move(int x,int y);
        virtual void moveTo(int x,int y);

        void setBgColor(u32 bgColor)
        {
            Element::bgColor = bgColor;
        }

        u32 bgColor;


    protected:

        virtual void onMeasure(sizeConstraint width, sizeConstraint height);
        //virtual void onLayout();
        virtual void onDraw(Canvas &canvas) const;
        virtual void onDrawScrollBars(Canvas &canvas) const;
        virtual void onSizeChanged();
        virtual void onClick();
        virtual void onHold();
        virtual void onFocus();
        virtual void onFocusLoss();
        virtual bool getFocusedElement(Element *&currentFocus);
        void bringToFront();

        Container *_upper = nullptr;
        Container *_root = nullptr;

        Rectangle _aabb;
        Size _measuredSize;

        int _depthLevel = 0;
        bool _hasFocus = false;
        bool _bringToFrontOnFocus = false;
        gfxScreen_t _screen;
        VISIBILITY _visibility;
    };

    using Element_shared_ptr = std::shared_ptr<Element>;


    template <class T,class ... Args>
    std::shared_ptr<T> make_elem(Args && ... args)
    {
        Derived_from<T,Element>();//Error if T does not derive from Element
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}