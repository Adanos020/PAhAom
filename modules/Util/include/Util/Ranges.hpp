#pragma once


#include <Util/Concepts.hpp>

#include <cstdint>
#include <type_traits>


namespace util
{

template<Integral T>
inline constexpr bool isInRange(const T& value, const T& lo, const T& hi)
{
        return static_cast<std::uint32_t>(value - lo) <= (hi - lo);
}

template<Floating T>
inline constexpr bool isInRange(const T& value, const T& lo, const T& hi)
{
        return value >= lo and value < hi;
}

}