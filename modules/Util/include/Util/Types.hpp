#pragma once


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>


namespace sf
{

using UintRect = Rect<unsigned>;

}


namespace util
{

// Aliases
using CStr = const char*;
using DeltaTime = float;

template<typename T>
using FastVector = std::basic_string<T, std::char_traits<T>>;

template<typename T>
using UniquePtrs = std::vector<std::unique_ptr<T>>;

template<typename T>
using MapStringTo = std::unordered_map<std::string, T>;

template<typename T>
using Matrix = std::vector<std::vector<T>>;


// Traits
template<class Type>
static constexpr bool isVectorType =
        std::is_same_v<Type, sf::Vector2f> or
        std::is_same_v<Type, sf::Vector3f>
;

template<typename T> constexpr bool isResource =
        std::is_same_v<T, sf::Font> or
        std::is_same_v<T, sf::Texture>
;

}