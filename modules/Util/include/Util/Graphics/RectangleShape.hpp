#pragma once


#include <Util/Graphics/Graphical.hpp>


namespace util::graphics
{

class RectangleShape : public Graphical, public sf::RectangleShape
{
public:
        RectangleShape(const Vector size = {0, 0})
        : sf::RectangleShape(size)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::RectangleShape&>(*this), states);
        }
};

}