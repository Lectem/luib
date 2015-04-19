#include <sf2d.h>
#include <UI/Draw.hpp>
#include "UI/Element.hpp"
#include "luib.hpp"

namespace luib {

    void Element::draw() const
    {
        draw::rectangle(aabb.x,aabb.y,aabb.w,aabb.h,bgColor);
    }

    bool Element::isTouched()
    {
        return screen == GFX_BOTTOM && kHeld&KEY_TOUCH && aabb.contains(touch.px,touch.py);
    }

    void Element::onClick()
    {
        bgColor^=0xFFFFFF00;
    }
}