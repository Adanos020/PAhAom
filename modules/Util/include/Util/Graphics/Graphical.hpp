#pragma once


#include <Util/Math.hpp>

#include <SFML/Graphics.hpp>

#include <memory>


namespace util::graphics
{

class Graphical : public sf::Drawable, public sf::Transformable
{
public:
        std::unique_ptr<Graphical> copy() const;
};

}