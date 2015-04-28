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
        if(visibility==VISIBLE) onDraw();
    }
    void Element::onDraw() const
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


    bool Element::getFocusedElement(Element *&currentFocus)
    {
        //todo : fix it
        if(currentFocus == NULL||currentFocus->depthLevel < depthLevel)
        {
            hasFocus = true;
            currentFocus = this;
            return true;
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

    void Element::move(int x, int y)
    {
        aabb.x+=x;
        aabb.y+=y;
    }

    void Element::moveTo(int x, int y)
    {
        aabb.x=x;
        aabb.y=y;
    }

    void Element::bringToFront()
    {
        if(bringToFrontOnFocus && upper != nullptr)
        {
            upper->bringToFront(this);
        }
    }
}