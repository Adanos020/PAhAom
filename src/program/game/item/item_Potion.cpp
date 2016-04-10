/**
 * @file src/program/game/item/Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: LLVM Clang Compiler
 */

#include "item_Potion.hpp"

#include <string>

extern std::map<sf::String, sf::String> dictionary;

namespace rr {

    Potion::Potion(Effect e, Size s, int am, sf::Vector2f pos) {
        name       = "";
        amount     = am;
        effect     = e;
        size       = s;
        disposable = true;
        discovered = false;
        ID         = 383;

        skin.loadFromFile("data/graphics/items.png");

        int tu = (size+1)%(280/14);
        int tv = (size+1)/(280/14);

        body.setTexture(skin);
        body.setTextureRect(sf::IntRect(tu*14, tv*14, 14, 14));
        body.scale(sf::Vector2f(5, 5));
        body.setPosition(pos);
    }

    Potion::~Potion() {}

    void Potion::reveal() {
        discovered = true;
    }

    void Potion::draw(sf::RenderWindow& rw) {
        rw.draw(body);
    }

    void Potion::editAmount(int am) {
        amount = am;
    }

    void Potion::update() {
        boundBox = body.getGlobalBounds();
    }

}
