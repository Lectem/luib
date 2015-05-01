/**
 * @file Container.hpp
 * @author Lectem
 * @date 14/04/2015
 */

#pragma once

#include "Element.hpp"
#include "Canvas.hpp"
#include <list>
#include <memory>

namespace luib {
    class Container : public Element
    {
        friend class Element;
        friend void ::luib::Update();
        friend void ::luib::findFocus();
    public:
        Container(int x = 0, int y = 0, int w = 0, int h = 0,u32 bgColor = RGBA8(0,0,0,0));

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

        /**
         * @brief Attaches an element to the container
         * @param element a shared pointer to the element.
         * @warning Since we are using shared pointers, keep in mind that if you don't keep a shared_ptr to the element, it might be destroyed by the UI.
         * Please remember it must NOT be allocated on the stack or it will be destroyed twice.
         */
        void attach(Element_shared_ptr element);
        void detach(Element_shared_ptr element);
        void detach(Element * element);


        virtual void bringToFront(Element * element);
        virtual void update() override;
        virtual void onDraw(Canvas &canvas) const override;


        virtual void move(int x, int y) override;

        virtual void moveTo(int x, int y) override;

    protected:
        virtual void onClick() override;
        virtual bool getFocusedElement(Element *&currentFocus) override;
        void clean();

        std::list<std::shared_ptr<Element>> children;
    };

    template<class T, class ... Args>
    std::shared_ptr<T> Container::add(Args &&... args)
    {
        Derived_from<T,Element>();
        std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(args)...);
        element->measure(_aabb.x, _aabb.y);
        if(element->_aabb.x+element->_aabb.w >= _aabb.w)
        {
            element->_aabb.w = _aabb.w -element->_aabb.x ;
        }
        if(element->_aabb.y+element->_aabb.h >= _aabb.h)
        {
            element->_aabb.h = _aabb.h -element->_aabb.y ;
        }
        element->_aabb.x+= _aabb.x;
        element->_aabb.y+= _aabb.y;
        element->_bringToFrontOnFocus |= _bringToFrontOnFocus;
        attach(element);
        return element;
    }

    using Container_shared_ptr = std::shared_ptr<Container>;

}