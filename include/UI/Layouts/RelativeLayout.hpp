//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "UI/Container.hpp"

namespace luib {
    class RelativeLayout : public Container
    {

    public:
        RelativeLayout(int x, int y, int w, int h);

    protected:
        virtual void onMeasure(sizeConstraint width, sizeConstraint height) override;
        virtual void onLayout(Rectangle const &coordinates) override;
    };

    using RelativeLayout_shared_ptr = std::shared_ptr<RelativeLayout>;

}