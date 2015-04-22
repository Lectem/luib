//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "UI/Element.hpp"
#include <string>
namespace luib {
    class Text : public Element
    {

    public:
        Text(int x, int y, int w, int h,std::string text);

        void draw() const;


    protected:
        virtual void onClick() override;

    private:
        std::string text;
    };
    using Text_shared_ptr = std::shared_ptr<Text>;

}

