#include <sf2d.h>
#include <UI/Draw.hpp>
#include "UI/Element.hpp"
#include "luib.hpp"
#include "UI/Container.hpp"
namespace luib {


    Element::~Element()
    {
        if(hasFocus)
        {
            ResetFocus();
        }
    }

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

    /**
     * Should update the size and/or values of the element
     */
    void Element::update()
    {
    }


    void Element::getFocusedElement(Element *&currentFocus)
    {
        if(currentFocus->depthLevel < depthLevel)
        {
            hasFocus = true;
            currentFocus = this;
        }
    }

    void Element::onFocus()
    {

    }

    void Element::onFocusLoss()
    {

    }

    void Element::onHold()
    {

    }
}