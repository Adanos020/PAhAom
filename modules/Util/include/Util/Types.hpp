#pragma once


#include <SFML/Graphics/Rect.hpp>

#include <cstdint>
#include <memory>
#include <stack>
#include <string>
#include <vector>


namespace sf
{

using UintRect = Rect<unsigned>;

}


namespace util
{

using DeltaTime = float;
using TileID = std::uint_fast8_t;

template<typename T>
using FastVector = std::basic_string<T, std::char_traits<T>>;

template<typename T>
using UniquePtrs = std::vector<std::unique_ptr<T>>;

}