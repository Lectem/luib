//
// Created by Lectem on 14/04/2015.
//
#pragma once

#include "Element.hpp"

namespace luib {
    class Container : public Element
    {
        std::vector<Element *> children;
    public:
        Container(int x = 0, int y = 0, int w = 0, int h = 0);

        ~Container();

        /**
         * Adds the element to the container children
         * This element will be deleted upon container deletion if freeUponDeletion is set.
         */
        template<class T, class ... Args>
        T *add(Args &&... args);

        virtual void draw() const;

        virtual void onClick() override;
    };


    template<class T, class ... Args>
    T *Container::add(Args &&... args)
    {
        T *element = new T(args...);
        children.push_back(element);
        element->upper = this;
        if (root != nullptr)element->root = root;
        else element->root = this;
        return element;
    }
}