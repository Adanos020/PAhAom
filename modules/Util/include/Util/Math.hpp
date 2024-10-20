#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Types.hpp>

#include <SFML/System/Vector2.hpp>

#include <sol/sol.hpp>

#include <cmath>
#include <iostream>
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


// Functions

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


// Types

template<Arithmetic T>
struct Vector : sf::Vector2<T>
{
        Vector() {}

        Vector(const T x, const T y)
        : sf::Vector2<T>(x, y)
        {
        }

        Vector(const Vector<T>& copy)
        : sf::Vector2<T>(copy)
        {
        }

        template<Arithmetic U>
        Vector(const sf::Vector2<U>& other)
        : sf::Vector2<T>(other)
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

public:

        inline static const Vector Zero = Vector(T{0}, T{0});
};

using FVector = Vector<float>;
using IVector = Vector<std::int32_t>;
using UVector = Vector<std::uint32_t>;

template<Arithmetic T>
class Matrix
{
public:

        Matrix(const Matrix<T>& copy)
        : r(copy.r)
        , c(copy.c)
        , data(copy.data)
        {
        }

        Matrix(const std::size_t r, const std::size_t c, const T fill = 0)
        : r(r)
        , c(c)
        , data(r * c, static_cast<T>(fill))
        {
        }

        template<typename InputRange>
        Matrix(const std::size_t r, const std::size_t c, InputRange input)
        : r(r)
        , c(c)
        , data(std::begin(input), std::end(input))
        {
                if (data.size() != this->r * this->c)
                {
                        std::cerr << "Size of input doesn't match given matrix bounds. Resizing." << std::endl;
                        data.resize(this->r * this->c);
                }
        }

        Matrix(const std::size_t r, const std::size_t c, sol::table input)
        : Matrix(r, c,
                [&] {
                        static const auto as_size = &sol::object::as<std::size_t>;
                        static const auto as_T = &sol::object::as<T>;

                        std::basic_string<T> data(r * c, static_cast<T>(0));
                        for (auto [i, x] : input)
                        {
                                if (x.get_type() != sol::type::number)
                                {
                                        std::cerr << util::err::notANumber << std::endl;
                                        continue;
                                }
                                data[(i.*as_size)()] = (x.*as_T)();
                        }
                        return data;
                }())
        {
        }

        T get(std::size_t row, std::size_t column) const
        {
                if (row > this->r or column > this->c)
                {
                        std::cerr << util::format("Matrix indices (%lu, %lu) out of bounds (%lu, %lu).",
                                row, column, this->r, this->c) << std::endl;
                        return static_cast<T>(-1);
                }
                return data[row + column * this->r];
        }

        void set(std::size_t row, std::size_t column, const T entry)
        {
                if (row > this->r or column > this->c)
                {
                        std::cerr << util::format("Matrix indices (%lu, %lu) out of bounds (%lu, %lu).",
                                row, column, this->r, this->c) << std::endl;
                        return;
                }
                data[row + column * this->r] = entry;
        }

public:

        Matrix<T>& operator=(const Matrix<T>& other)
        {
                this->r = other.r;
                this->c = other.c;
                this->data = other.data;
                return *this;
        }

public:

        std::size_t rows() const
        {
                return this->r;
        }

        std::size_t columns() const
        {
                return this->c;
        }

private:

        std::size_t r;
        std::size_t c;
        std::basic_string<T> data;
};

}