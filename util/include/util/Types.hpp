#pragma once


#include <SFML/Graphics/Rect.hpp>

#include <cstdint>
#include <string>


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

}