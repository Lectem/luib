#include <sf2d.h>
#include <Inputs.h>
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

    void Element::layout(Rectangle const & coordinates)
    {
        //Either forced or different size has been given
        if(_isLayoutNeeded || coordinates != _aabb)
        {
            _aabb = coordinates;
            onLayout(coordinates);
        }
        _isLayoutNeeded = false;
    }

    int Element::getWidth() const
    {
        return _aabb.w;
    }

    int Element::getHeight() const
    {
        return _aabb.h;
    }

    void Element::draw(Canvas &canvas) const
    {
        if(_visibility ==VISIBLE)
        {
            drawBG(canvas);
            onDraw(canvas);
        }
    }


    void Element::drawBG(Canvas &canvas) const
    {
        canvas.rectangle(0,0,getWidth(),getHeight(),bgColor);
    }

    bool Element::isTouched()
    {
        return _screen == GFX_BOTTOM && kHeld&KEY_TOUCH && _aabb.contains(touch.px,touch.py);
    }

    void Element::onTouchEvent(const TouchEvent &touchEvent)
    {
        bgColor^=0xFFFFFF00;
    }


    bool Element::getFocusedElement(Element *&currentFocus,TouchEvent & touchEvent)
    {
        //todo : fix it
        if(currentFocus == NULL||currentFocus->_depthLevel < _depthLevel)
        {
            currentFocus = this;
            return true;
        }
        return false;
    }



    void Element::move(int x, int y)
    {
        if(_upper)_upper->moveChild(this,x,y);
        requestLayout();
    }

    void Element::moveTo(int x, int y)
    {
        if(_upper)_upper->moveChildTo(this,x,y);
        requestLayout();
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
        setMeasuredSize(width.value,height.value);
    }


    void Element::detachFromParent()
    {
        if(_upper)_upper->detach(this);
    }

    Size Element::getMeasuredSize() const
    {
        return _measuredSize;
    }

    void Element::setMeasuredSize(const Size measuredSize)
    {
        _measuredSize = _measuredSize;
    }

    void Element::setMeasuredSize(const int width, const int height)
    {
        _measuredSize.x = width;
        _measuredSize.y = height;
    }

    void Element::requestLayout()
    {
        _isLayoutNeeded=true;
        if(_upper)_upper->requestLayout();
    }

    void Element::forceLayout()
    {
        _isLayoutNeeded = true;
    }
    void Element::setBgColor(u32 bgColor)
    {
        Element::bgColor = bgColor;
    }

}

