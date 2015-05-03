//
// Created by Lectem on 14/04/2015.
//

#include "UI/Widgets/Button.hpp"

namespace luib{

    Button::Button(int x, int y, int w, int h) : Element(x, y, w, h)
    {

    }

    void Button::onTouchEvent(const luib::TouchEvent &touchEvent)
    {
        if (touchEvent.type == TouchEvent::DOWN)
        {
            if(_onClickListener)_onClickListener(*this);
        }
    }

    void Button::setOnClickListener(Button::OnClickListener onClickListener)
    {
        _onClickListener=onClickListener;
    }
}