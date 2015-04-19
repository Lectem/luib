/**
 *@file utils.hpp
 *@author Lectem
 *@date 19/04/2015
 */
#pragma once
namespace luib{
    template<class T, class B> struct Derived_from {
        static void constraints(T* p) { B* pb = p;(void)pb; }
        Derived_from() { void(*p)(T*) = constraints;(void)p; }
    };
}