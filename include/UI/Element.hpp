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
    public:
        Element(int x =0 ,int y = 0,int w = 1,int h = 1):
                bgColor(RGBA8(0xFF,0,0,0xFF)),
                aabb{x,y,w,h}
        {
            screen=GFX_BOTTOM;
            printf("Element created\n");
        }
        virtual ~Element();
        virtual void draw() const;
        virtual bool isTouched();
        virtual void onClick();
        u32 bgColor;
    protected:
        Rectangle aabb;
        Container *upper = nullptr;
        Container *root = nullptr;
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