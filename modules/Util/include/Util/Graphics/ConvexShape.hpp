#pragma once


#include <Util/Graphics/Graphical.hpp>


namespace util::graphics
{

class ConvexShape : public Graphical, public sf::ConvexShape
{
public:
        ConvexShape(const std::size_t pointCount = 0)
        : sf::ConvexShape(pointCount)
        {
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
                target.draw(static_cast<const sf::ConvexShape&>(*this), states);
        }
};

}