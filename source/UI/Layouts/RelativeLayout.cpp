//
// Created by Lectem on 14/04/2015.
//

#include "UI/Layouts/RelativeLayout.hpp"
namespace luib {
    RelativeLayout::RelativeLayout(int x, int y, int w, int h) : Container(x, y, w, h)
    {

    }

    void RelativeLayout::onMeasure(sizeConstraint width, sizeConstraint height)
    {
        //printf("RelativeLayout::onMeasure\n");
        setMeasuredSize(width.value,height.value);
        width.type=sizeConstraint::AT_MOST;
        height.type=sizeConstraint::AT_MOST;
        for(auto &childPtr :_children)
        {
            childPtr->measure(width,height);
        }
    }


    void RelativeLayout::onLayout(Rectangle const &coordinates)
    {
        for(auto &childPtr :_children)
        {
            Rectangle aabb = getChildAABB(childPtr.get());
            aabb.w=childPtr->getMeasuredSize().x;
            aabb.h=childPtr->getMeasuredSize().y;
            childPtr->layout(aabb);
        }
    }
}