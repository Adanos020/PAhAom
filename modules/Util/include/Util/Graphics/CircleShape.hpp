#pragma once


#include <Util/Graphics/Graphical.hpp>


namespace util::graphics
{

class CircleShape : public Graphical, public sf::CircleShape
{
public:
        CircleShape(const float radius = 0, const std::size_t pointCount = 30)
        : sf::CircleShape(radius, pointCount)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::CircleShape&>(*this), states);
        }
};

}