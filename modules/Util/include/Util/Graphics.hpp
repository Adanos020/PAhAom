#pragma once


#include <Util/Graphics/RectTileMap.hpp>

#include <type_traits>


namespace util
{

template<class T>
concept Drawable = std::is_base_of_v<sf::Drawable, T>;

template<class T>
concept Transformable = std::is_base_of_v<sf::Transformable, T>;

template<class T>
concept Graphical = Drawable<T> and Transformable<T>;

}