/**
 * @file src/program/game/item/item_Coin.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_Coin_hpp
#define item_Coin_hpp

#include "item.hpp"

namespace rr {

	class Coin : public Item {
    public:
        enum Type {
            GOLDEN,
            SILVER,
            BRONZE
        } type_;
        enum Size {
            SMALL,
            BIG
        } size_;

         Coin(Type, Size, int am, sf::Vector2i pos);
        ~Coin() {}

        virtual void draw(sf::RenderWindow&) override;
	};

}

#endif // item_Coin_hpp

