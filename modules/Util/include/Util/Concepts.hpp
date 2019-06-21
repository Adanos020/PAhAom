#pragma once


#include <SFML/Graphics/Drawable.hpp>

#include <type_traits>


namespace util
{

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept Drawable = std::is_base_of_v<sf::Drawable, T>;

template<typename T>
concept Floating = std::is_floating_point_v<T>;

}