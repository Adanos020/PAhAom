#pragma once


#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <cmath>
#include <type_traits>


namespace util
{

namespace impl
{
        template<class Type>
        static constexpr bool isVectorType =
                std::is_same_v<Type, sf::Vector2f> or std::is_same_v<Type, sf::Vector3f>;
}

template<class Type>
inline Type lerp(const Type val1, const Type val2, const Type alpha)
{
        return (1.0 - alpha) * val1 + alpha * val2;
}

inline double normalize(const double val, const double lo, const double hi)
{
        return (val - lo) / (hi - lo);
}

inline double mapNumber(const double val, const double lo1, const double hi1,
                        const double lo2, const double hi2)
{
        return normalize(val, lo1, hi1) * (hi2 - lo2) + lo2;
}

template <>
inline sf::Vector2f lerp(const sf::Vector2f vec1, const sf::Vector2f vec2, const sf::Vector2f alpha)
{
        return {
                lerp(vec1.x, vec2.x, alpha.x),
                lerp(vec1.y, vec2.y, alpha.y),
        };
}

template <>
inline sf::Vector3f lerp(const sf::Vector3f vec1, const sf::Vector3f vec2, const sf::Vector3f alpha)
{
        return {
                lerp(vec1.x, vec2.x, alpha.x),
                lerp(vec1.y, vec2.y, alpha.y),
                lerp(vec1.y, vec2.y, alpha.z),
        };
}

template<class VectorType>
inline float vecLengthSquared(const VectorType vec)
{
        static_assert(impl::isVectorType<VectorType>);
        if constexpr (std::is_same_v<VectorType, sf::Vector2f>)
        {
                return vec.x * vec.x + vec.y * vec.y;
        }
        else
        {
                return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
        }
}

template<class VectorType>
inline float vecLength(const VectorType vec)
{
        static_assert(impl::isVectorType<VectorType>);
        return std::sqrt(vecLengthSquared(vec));
}

template<class VectorType>
inline VectorType normalize(const VectorType vec)
{
        static_assert(impl::isVectorType<VectorType>);
        return vec / vecLength(vec);
}

template<class VectorType>
inline VectorType vecSetLength(const VectorType vec, const float len)
{
        static_assert(impl::isVectorType<VectorType>);
        return normalize(vec) * len;
}

}