/**
 * @file src/program/game/entity/Stairs.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../Resources.hpp"

#include "../../funcs/files.hpp"

#include "Stairs.hpp"

namespace rr {

    Stairs::Stairs(bool upwards) :
      upwards_ (upwards)
    {
        initialize();
    }

    Stairs::Stairs(Stairs const& copy) :
      body_   (copy.body_   ),
      upwards_(copy.upwards_) {}

    void Stairs::initialize() {
        body_.setTexture    (Resources::texture.objects);
        body_.setScale      (sf::Vector2f(5, 5));
        body_.setTextureRect(sf::IntRect(upwards_ ? 16 : 0, 64, 16, 16));
    }

    void Stairs::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &Resources::texture.objects;
        target.draw(body_, states);
    }

    std::ifstream& Stairs::operator<<(std::ifstream& file) {
        sf::Vector2u position;

        try {
            readFile <unsigned> (file, position.x);
            readFile <unsigned> (file, position.y);
            readFile <  bool  > (file, upwards_);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Stairs::operator>>(std::ofstream& file) {
        file << 42                                   << ' '
             << (unsigned) body_.getPosition().x/80u << ' '
             << (unsigned) body_.getPosition().y/80u << ' '
             << upwards_;

        return file;
    }

}
