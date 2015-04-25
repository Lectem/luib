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

        /**
         * @brief Returns the width of a character.
         * Will be used for variable width fonts
         */
        static int getCharWidth(char  str ) ;//TODO move to font struct

        /**
         * @brief Returns the width of an whole word with padding included
         * @param str points to the beginning of a word
         * @param nbCharacters will store the number of characters of the word
         */
        static int getWordWidth(const char * str, int & nbCharacters ) ;//TODO move to font struct
    private:
        static const int fontPadding = 1;//TODO move to font struct
        std::string text;
    };

    using Text_shared_ptr = std::shared_ptr<Text>;

}

