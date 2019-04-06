#pragma once


#include <SFML/Graphics/Rect.hpp>

#include <cstdint>
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

using CStr = const char*;
using DeltaTime = float;
using TileID = std::uint_fast8_t;
using IconIndex = std::size_t;

template<typename T>
using FastVector = std::basic_string<T, std::char_traits<T>>;

template<typename T>
using UniquePtrs = std::vector<std::unique_ptr<T>>;

template<typename T>
using MapStringTo = std::unordered_map<std::string, T>;

template<typename T>
using Matrix = FastVector<FastVector<T>>;

}