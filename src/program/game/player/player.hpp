/**
 * @file src/program/game/player/player.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef player_h
#define player_h

#include <SFML/Graphics.hpp>
#include "../../../../lib/AnimatedSprite.hpp"

namespace rr {

/// Class for the player
    class Player {
        friend class Game;
    private:
        struct Stats {
        public:
            double hp;
            double mp;
            double maxhp;
            double maxmp;
            int    sp;
            int    exp;
            int    nextlvl;
            int    lvl;
        };

        sf::Vector2f       position;
        sf::AnimatedSprite body;
        sf::Animation      walkingLeft;
        sf::Animation      walkingRight;
        sf::Animation*     currentAnimation;
        Stats              stats;
        double             velocity;
    public:
         Player(sf::Vector2f pos);
        ~Player();

        enum direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        void         setPosition(sf::Vector2f);
        void         go         (float timeStep, direction);
        void         draw       (sf::RenderWindow&);
        void         update     ();

        Stats        getStats   () const { return stats; }
        sf::Vector2f getPosition() const { return body.getPosition(); }
    };

}

#endif // player_h
