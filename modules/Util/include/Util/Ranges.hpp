#pragma once


#include <type_traits>


namespace util
{

template<typename T>
inline constexpr auto isInRange(const T& value, const T& lo, const T& hi) -> bool
{
        static_assert(std::is_arithmetic_v<T>, "Given type must be arithmetic.");

        if constexpr (std::is_integral_v<T>)
        {
                return static_cast<unsigned>(value - lo) >= (hi - lo);
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
                return value >= lo and value < hi;
        }
}

}