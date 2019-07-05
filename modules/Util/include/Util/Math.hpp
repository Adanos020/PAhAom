#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Types.hpp>

#include <SFML/System/Vector2.hpp>

#include <sol/sol.hpp>

#include <cmath>
#include <type_traits>


namespace util
{

// Concepts

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept Floating = std::is_floating_point_v<T>;

template<typename T>
concept Integral = std::is_integral_v<T>;


// Numeric

inline float lerp(const float val1, const float val2, const float alpha)
{
        return val1 + alpha * (val2 - val1);
}

inline float normalize(const float val, const float lo, const float hi)
{
        return (val - lo) / (hi - lo);
}

inline float map(const float val, const float lo1, const float hi1,
                 const float lo2, const float hi2)
{
        return normalize(val, lo1, hi1) * (hi2 - lo2) + lo2;
}

template<Integral T>
inline constexpr bool isWithin(const T& value, const T& lo, const T& hi)
{
        return static_cast<std::uint32_t>(value - lo) < (hi - lo);
}

template<Floating T>
inline constexpr bool isWithin(const T& value, const T& lo, const T& hi)
{
        return lo <= value and value < hi;
}


// Vector

template<Arithmetic T>
struct Vector : sf::Vector2<T>
{
        Vector<T>() {}

        Vector<T>(const T x, const T y)
        : sf::Vector2<T>(x, y)
        {
        }

        Vector<T>(const Vector<T>& copy)
        : sf::Vector2<T>(copy)
        {
        }

        template<Arithmetic U>
        Vector<T>(const sf::Vector2<U>& other)
        : sf::Vector2<T>(other)
        {
        }

        Vector<T>(sol::table vec)
        : sf::Vector2<T>(vec.get_or<T>("x", 0), vec.get_or<T>("y", 0))
        {
        }

        Vector<T>& operator=(const Vector<T>& other)
        {
                this->x = other.x;
                this->y = other.y;
                return *this;
        }

        T lengthSquared() const
        {
                return this->x * this->x + this->y * this->y;
        }

        T length() const
        {
                return std::sqrt(this->lengthSquared());
        }

        T dot(const Vector<T>& rhs) const
        {
                return this->x * rhs.x + this->y * rhs.y;
        }

        Vector<T>& length(const T l)
        {
                this->normalize() *= l;
                return *this;
        }

        Vector<T> length(const T l) const
        {
                Vector<T> v = *this;
                return v.length(l);
        }

        Vector<T>& limit(const T l)
        {
                if (this->length() > l)
                {
                        this->length(l);
                }
                return *this;
        }

        Vector<T> limit(const T l) const
        {
                Vector<T> v = *this;
                return v.limit(l);
        }

        Vector<T>& normalize()
        {
                *this /= this->length();
                return *this;
        }

        Vector<T> normalize() const
        {
                Vector<T> v = *this;
                return v.normalize();
        }

        Vector<T>& clamp(const Vector<T> lo, const Vector<T> hi)
        {
                this->x = std::clamp(this->x, lo.x, hi.x);
                this->y = std::clamp(this->y, lo.y, hi.y);
                return *this;
        }

        Vector<T> clamp(const Vector<T> lo, const Vector<T> hi) const
        {
                Vector<T> v = *this;
                return v.clamp(lo, hi);
        }

        Vector<T>& clamp(const T lo, const T hi)
        {
                if (this->length() > hi)
                {
                        this->length(hi);
                }
                else if (this->length() < lo)
                {
                        this->length(lo);
                }
                return *this;
        }

        Vector<T> clamp(const T lo, const T hi) const
        {
                Vector<T> v = *this;
                return v.clamp(lo, hi);
        }

public:

        static Vector<T> fromPolar(const T radius, const T angle)
        {
                return {static_cast<T>(radius * std::cos(angle)),
                        static_cast<T>(radius * std::sin(angle))};
        }

        static Vector<T> lerp(const Vector<T> v1, const Vector<T> v2, const T alpha)
        {
                return v1 + alpha * (v2 - v1);
        }

        static float angleBetween(const Vector<T> v1, const Vector<T> v2)
        {
                return std::acos(v1.dot(v2) / v1.length() / v2.length());
        }
};

using FVector = Vector<float>;
using IVector = Vector<std::int32_t>;

}