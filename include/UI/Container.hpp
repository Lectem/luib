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
#include <Inputs.h>

namespace luib {
    class Container : public Element
    {
        friend class Element;
        friend void Update();
        friend void dispatchTouchEvent(TouchEvent touchEvent);
    public:
        Container(int x = 0, int y = 0, int w = 0, int h = 0,u32 bgColor = 0);
        Container(LayoutParams layoutParams);

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

        virtual /**
         * @brief Attaches an element to the container
         * @param element a shared pointer to the element.
         * @warning Since we are using shared pointers, keep in mind that if you don't keep a shared_ptr to the element, it might be destroyed by the UI.
         * Please remember it must NOT be allocated on the stack or it will be destroyed twice.
         */
        void attach(Element_shared_ptr element);

        /**
         * @brief Detaches an element from the container
         *
         * @note You can reattach an element to anther container as long as you keep a
         * shared_ptr to the element while it is detached.
         */
        void detach(Element_shared_ptr element);
        void detach(Element * element);

        /**
         * @brief Brings an element to the front of the container
         * Bringing an element to the front can be useful if elements can overlap in your container
         * This is a thing to do when an element is focused
         */
        virtual void bringToFront(Element * element);

        /**
         * @brief Move the container and its content
         * @param x the number of pixels to move by horizontally
         * @param y the number of pixels to move by vertically
         */
        virtual void move(int x, int y) override;

        /**
         * @brief Move the container and its content to specific loctaion
         *
         * It will move the container within its parent to the offset given
         *
         * @param x the horizontal offset, relatively to the parent
         * @param x the horizontal offset, relatively to the parent
         */
        virtual void moveTo(int x, int y) override;

        /**
         * @brief Move the child within the bounds of the container
         * @param x the number of pixels to move by horizontally
         * @param y the number of pixels to move by vertically
         */
        virtual void moveChild(Element * child,int x, int y);

        /**
         * Same as moveChild, but giving the offset instead of a difference
         */
        virtual void moveChildTo(Element * child,int x, int y);

    protected:
        void setChildAABB(Element* child,Rectangle const & aabb);
        Rectangle       & getChildAABB(Element* child) ;
        Rectangle const & getChildAABB(Element* child) const;

        /**
         * Ask all _children to measure themselves.
         * Children that are with the visibility GONE are ignored
         */
        void measureChildren(sizeConstraint width, sizeConstraint height);

        /**
         * Ask a child to measure itself taking into account the padding
         * and the sizeConstraint of this Container
         */
        void measureChild(Element_shared_ptr child,sizeConstraint width, sizeConstraint height);

        /**
         * Default layout parameter for children
         */
        int getDefaultLayoutParams(){
            return LayoutParams::WRAP_CONTENT;
        }

        /**
         * The most difficult part of the measuring step, it helps to choose
         * what constraints will be given to _children based on their LayoutParam.
         * @param constraint The constraint of a dimension (width|height) for this Container
         * @padding The total padding of this dimension
         * @childParams The parameters of the child
         * @return The constraint to be given to the child
         */
        sizeConstraint getChildSizeContraint(sizeConstraint constraint,int padding,int childParam);


        virtual void onMeasure(sizeConstraint width, sizeConstraint height) override;
        virtual void onLayout(Rectangle const &coordinates) override;
        virtual void onDraw(Canvas &canvas) const override;
        virtual void onAttach(Element * element);
        virtual void onDetach(Element * element);
        virtual void onTouchEvent(const TouchEvent &touchEvent) override;
        void clean();

        virtual bool findFocusedElement(Element *&currentFocus, TouchEvent &touchEvent) override;

        std::vector<std::shared_ptr<Element>> _children;
        Padding _padding;
    private:
    };

    template<class T, class ... Args>
    std::shared_ptr<T> Container::add(Args &&... args)
    {
        Derived_from<T,Element>();
        std::shared_ptr<T> element = std::make_shared<T>(std::forward<Args>(args)...);
        attach(element);
        return element;
    }

    using Container_shared_ptr = std::shared_ptr<Container>;

}