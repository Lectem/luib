//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "UI/Element.hpp"

namespace luib {
    class Button : public Element
    {

    public:
        using OnClickListener = std::function<void(Element&)>;
        ~Button(){printf("Button freed\n");}
        Button(int x, int y, int w, int h);
        void setOnClickListener(OnClickListener onClickListener);
    protected:
        virtual void onTouchEvent(const luib::TouchEvent &touchEvent) override;
        OnClickListener _onClickListener;
    };
        using Button_shared_ptr = std::shared_ptr<Button>;

}

