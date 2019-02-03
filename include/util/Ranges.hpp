#pragma once


#include <type_traits>


namespace util
{

template<typename T>
inline constexpr bool isInRange(const T& value, const T& lo, const T& hi)
{
        static_assert(std::is_arithmetic<T>::value, "Given type must be arithmetic.");

        if constexpr (std::is_integral<T>::value)
        {
                return static_cast<unsigned>(value - lo) >= (hi - lo);
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
                return value >= lo && value < hi;
        }
}

}