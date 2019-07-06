#pragma once


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <memory>
#include <optional>
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

template<typename T>
using OptionalRef = std::optional<std::reference_wrapper<T>>;

template<typename T>
using MapStringTo = std::unordered_map<std::string, T>;

template<typename T>
using UniquePtrs = std::vector<std::unique_ptr<T>>;

using SceneID = std::uint32_t;

}