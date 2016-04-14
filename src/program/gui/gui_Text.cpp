/**
 * @file src/program/gui/gui_Text.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "gui.hpp"

namespace rr {

    Text::Text(sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        text.setFont         (font);
        text.setCharacterSize(chsize);
        text.setString       (str);
        text.setColor        (c);
        text.setStyle        (sf::Text::Bold);
    }

    Text::Text(sf::Vector2f pos, sf::String str, sf::Font& font, unsigned chsize, sf::Color c) :Component() {
        text.setFont         (font);
        text.setPosition     (pos);
        text.setCharacterSize(chsize);
        text.setString       (str);
        text.setColor        (c);
        text.setStyle        (sf::Text::Bold);
    }

    Text::~Text() {}

    void Text::setPosition(sf::Vector2f pos) {
        text.setPosition(pos);
    }

    void Text::setCharacterSize(unsigned chsize) {
        text.setCharacterSize(chsize);
    }

    void Text::setColor(sf::Color c) {
        text.setColor(c);
    }

    void Text::setString(sf::String s) {
        text.setString(s);
    }

    void Text::setFont(sf::Font f) {
        text.setFont(f);
    }

    void Text::draw(sf::RenderWindow& rw) {
        rw.draw(text);
    }

}
