/**
 * @file Container.hpp
 * @author Lectem
 * @date 14/04/2015
 */

#pragma once

#include "Element.hpp"
#include <list>
#include <memory>

namespace luib {
    class Container : public Element
    {
    friend class Element;
        std::list<std::shared_ptr<Element>> children;
    public:
        Container(int x = 0, int y = 0, int w = 0, int h = 0);

        ~Container();

        /**
         * @brief Adds an element to the container
         * @tparam T the type of element to be added.
         * @param args The arguments of the element constructor
         * @return A shared pointer to the element.
         * This element will be deleted upon container deletion if freeUponDeletion is set.
         */
        template<class T, class ... Args>
        std::shared_ptr<T> add(Args &&... args);

        void attach(Element_shared_ptr element);
        void detach(Element_shared_ptr element);
        void detach(Element * element);

        virtual void draw() const;

        virtual void onClick() override;

    };

    template<class T, class ... Args>
    std::shared_ptr<T> Container::add(Args &&... args)
    {
        std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(args)...);
        element->upper = this;
        if (root != nullptr)element->root = root;
        else element->root = this;

        children.emplace_back(element);
        return element;
    }

    using Container_shared_ptr = std::shared_ptr<Container>;

}