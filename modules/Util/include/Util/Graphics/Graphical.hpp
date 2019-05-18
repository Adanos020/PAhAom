#pragma once


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>


namespace util::graphics
{

class Graphical : public sf::Drawable, public sf::Transformable
{
};

}