/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef item_funcs_h
#define item_funcs_h

#include "../game/item/item.hpp"

namespace rr {

    inline Item* getItemFromID(double ID, int amount, sf::Vector2f pos) {
        /*unknown ID?*/
        return new Potion(Potion::Effect::HEALING, Potion::Size::BIG, amount, pos);
    }

}

#endif // item_funcs_h
