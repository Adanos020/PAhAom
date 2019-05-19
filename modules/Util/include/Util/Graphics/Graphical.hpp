#pragma once


#include <SFML/Graphics.hpp>

#include <memory>


namespace util::graphics
{

class Graphical : public sf::Drawable, public sf::Transformable
{
public:

        virtual std::unique_ptr<Graphical> copy() const = 0;
};

}