/**
 * @file src/program/game/item/item_Book.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "item_Book.hpp"
#include "../../../program.hpp"

extern rr::Resources resources;
extern sf::Color potionColors[9];

namespace rr {

    Book::Book(Type type, int am, sf::Vector2i pos) {
        _type       = type;
        _amount     = am;
        _ID         = _type+10;
        _discovered = false;
        _disposable = true;

        _body.resize(4);
        _body.setPrimitiveType(sf::Quads);

        _body[0].position = (sf::Vector2f)pos*80.f;
        _body[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
        _body[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        _body[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        int tu = 0;
        int tv = 1;

        _body[0].texCoords = sf::Vector2f(  tu  *16+0.03125f,   tv  *16+0.03125f);
        _body[1].texCoords = sf::Vector2f((tu+1)*16-0.03125f,   tv  *16+0.03125f);
        _body[2].texCoords = sf::Vector2f((tu+1)*16-0.03125f, (tv+1)*16-0.03125f);
        _body[3].texCoords = sf::Vector2f(  tu  *16+0.03125f, (tv+1)*16-0.03125f);

        for (int i=0; i<4; i++) {
            _body[i].color = potionColors[_type];
        }
    }

    Book::~Book() {}

    void Book::draw(sf::RenderWindow& rw) {
        rw.draw(_body, &resources.texture.items);
    }

    void Book::update() {}

    void Book::reveal() {
        _discovered = true;
    }

}
