#include <sf2d.h>
#include "UI/Canvas.hpp"
#include "UI/Element.hpp"
#include "luib.hpp"
#include "UI/Container.hpp"
namespace luib {


    Element::~Element()
    {
        if(_hasFocus)
        {
            ResetFocus();
        }
    }

    void Element::measure(sizeConstraint width, sizeConstraint height)
    {
        onMeasure(width, height);
    }

    void Element::draw(Canvas &canvas) const
    {
        if(_visibility ==VISIBLE) onDraw(canvas);
    }


    void Element::onDraw(Canvas &canvas) const
    {
        canvas.rectangle(_aabb.x, _aabb.y, _aabb.w, _aabb.h,bgColor);
    }

    void Element::onDrawScrollBars(Canvas &canvas) const
    {

    }

    bool Element::isTouched()
    {
        return _screen == GFX_BOTTOM && kHeld&KEY_TOUCH && _aabb.contains(touch.px,touch.py);
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
        if(currentFocus == NULL||currentFocus->_depthLevel < _depthLevel)
        {
            _hasFocus = true;
            currentFocus = this;
            return true;
        }
        return false;
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
        _aabb.x+=x;
        _aabb.y+=y;
    }

    void Element::moveTo(int x, int y)
    {
        _aabb.x=x;
        _aabb.y=y;
    }

    void Element::bringToFront()
    {
        if(_bringToFrontOnFocus && _upper != nullptr)
        {
            _upper->bringToFront(this);
        }
    }

    void Element::onMeasure(sizeConstraint width, sizeConstraint height)
    {
        if(_aabb.w > width.value) _aabb.w = width.value;
        if(_aabb.h > height.value) _aabb.h = height.value;
    }

    void Element::onSizeChanged()
    {

    }
}

