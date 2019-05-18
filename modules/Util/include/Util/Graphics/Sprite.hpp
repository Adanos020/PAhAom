#pragma once


#include <Util/Graphics/Graphical.hpp>


namespace util::graphics
{

class Sprite : public Graphical, public sf::Sprite
{
public:

        Sprite()
        : sf::Sprite()
        {
        }

        Sprite(const sf::Texture& texture)
        : sf::Sprite(texture)
        {
        }

        Sprite(const sf::Texture& texture, const sf::IntRect& rectangle)
        : sf::Sprite(texture, rectangle)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::Sprite&>(*this), states);
        }
};

}