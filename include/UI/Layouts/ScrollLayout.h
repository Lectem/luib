/**
 *@file ScrollLayout.h
 *@author Lectem
 *@date 07/05/2015
 */
#pragma once

#include "UI/Container.hpp"

namespace luib {
    class ScrollLayout : public Container
    {
    public:

        ScrollLayout(int x, int y, int w, int h, u32 bgColor);

        const Point &getScrollPos() const
        {
            return scrollPos;
        }

        void setScrollPos(const Point &scrollPos)
        {
            ScrollLayout::scrollPos = scrollPos;
        }

    protected:
        void onDraw(Canvas &canvas) const override;
        Point scrollPos;
    };

    using ScrollLayout_shared_ptr = std::shared_ptr<ScrollLayout>;

}