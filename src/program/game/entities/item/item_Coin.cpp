/**
 * @file src/program/game/item/item_Coin.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Coin.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;

namespace rr {

    Coin::Coin(Type t, Size s, int am, sf::Vector2i pos) {
        amount_ = am;
        type_   = t;
        size_   = s;
        ID_     = 3*size_ + type_ + 1;

        body_.resize(4);
        body_.setPrimitiveType(sf::Quads);

        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        int tu = (type_+(size_+2)*16)%16;
        int tv = (type_+(size_+2)*16)/16;

        body_[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        body_[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        body_[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        body_[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);
    }

    Coin::~Coin() {}

    void Coin::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Coin::update() {}

}
