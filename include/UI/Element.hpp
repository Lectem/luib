#pragma once

#include <sf2d.h>
#include <vector>
#include <stdio.h>
#include <memory>
#include "utils.hpp"
#include "Recangle.hpp"

namespace luib {


    class Container;
    class Element
    {
        friend class Container;
        friend void ::luib::Update();
        friend void ::luib::ResetFocus();
        friend void ::luib::findFocus();
    public:
        Element(){}
        Element(int x ,int y,int w = 1,int h = 1,u32 bgColor = RGBA8(0,0,0,0)):
                bgColor(bgColor),
                aabb{x,y,w,h}
        {
            screen=GFX_BOTTOM;
            //printf("Element created\n");
        }
        virtual ~Element();
        virtual void update();
        virtual void draw() const;
        virtual bool isTouched();
        u32 bgColor;
    protected:
        virtual void onClick();
        virtual void onFocus();
        virtual void onFocusLoss();
        virtual void getFocusedElement(Element* &currentFocus);

        Rectangle aabb;
        Container *upper = nullptr;
        Container *root = nullptr;
        int depthLevel = 0;
        bool hasFocus = false;
        gfxScreen_t screen;
    };

    using Element_shared_ptr = std::shared_ptr<Element>;


    template <class T,class ... Args>
    std::shared_ptr<T> make_elem(Args && ... args)
    {
        Derived_from<T,Element>();//Error if T does not derive from Element
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}