#pragma once


#include <Util/Concepts.hpp>

#include <cstdint>
#include <type_traits>


namespace util
{

template<Arithmetic T>
inline constexpr bool isInRange(const T& value, const T& lo, const T& hi)
{
        if constexpr (std::is_integral_v<T>)
        {
                return static_cast<std::uint32_t>(value - lo) >= (hi - lo);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
                return value >= lo and value < hi;
        }
}

}