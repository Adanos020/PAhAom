#pragma once


#include <Script/Lua.hpp>
#include <Util/Math.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>


namespace script
{

namespace impl
{
        template<util::Arithmetic T>
        inline static void registerVectorUserType(const std::string& name)
        {
                lua.new_usertype<sf::Vector2<T>>("sf" + name,
                        sol::constructors<
                                sf::Vector2<T>(),
                                sf::Vector2<T>(T, T),
                                sf::Vector2<T>(sf::Vector2i&),
                                sf::Vector2<T>(sf::Vector2f&)>(),
                        "x", &sf::Vector2<T>::x,
                        "y", &sf::Vector2<T>::y,
                        "add",      std::plus<sf::Vector2<T>>{},
                        "subtract", std::minus<sf::Vector2<T>>{},
                        "multiply", [](const sf::Vector2<T>& v, T x) { return v * x; },
                        "divide",   [](const sf::Vector2<T>& v, T x) { return v / x; },
                        "inverse",  std::negate<sf::Vector2<T>>{});

                using VT = util::Vector<T>;
                lua.new_usertype<VT>(name,
                        sol::constructors<
                                VT(),
                                VT(T, T),
                                VT(util::IVector&),
                                VT(util::FVector&),
                                VT(sf::Vector2i&),
                                VT(sf::Vector2f&)>(),
                        sol::base_classes, sol::bases<sf::Vector2<T>>{},
                        "lengthSquared", &VT::lengthSquared,
                        "length",        sol::property(
                                static_cast<T(VT::*)() const>(&VT::length),
                                static_cast<VT(VT::*)(T) const>(&VT::length)),
                        "dot",       &VT::dot,
                        "limit",     static_cast<VT(VT::*)(T) const>(&VT::limit),
                        "normalize", static_cast<VT(VT::*)() const>(&VT::normalize),
                        "clamp",     sol::overload(
                                static_cast<VT(VT::*)(VT, VT) const>(&VT::clamp),
                                static_cast<VT(VT::*)(T, T) const>(&VT::clamp)),
                        "fromPolar",    VT::fromPolar,
                        "angleBetween", VT::angleBetween,
                        "lerp",         VT::lerp);
        }

        template<util::Arithmetic T>
        inline static void registerRectangleUserType(const std::string& name)
        {
                using RT = sf::Rect<T>;
                lua.new_usertype<RT>(name,
                        sol::constructors<
                                RT(),
                                RT(sf::Vector2<T>, sf::Vector2<T>),
                                RT(T, T, T, T)>(),
                        "left",   &RT::left,
                        "top",    &RT::top,
                        "width",  &RT::width,
                        "height", &RT::height,
                        "contains", sol::overload(
                                static_cast<bool(RT::*)(const sf::Vector2<T>&) const>(&RT::contains),
                                static_cast<bool(RT::*)(T, T) const>(&RT::contains)),
                        "intersects", sol::overload(
                                static_cast<bool(RT::*)(const RT&) const>(&RT::intersects),
                                static_cast<bool(RT::*)(const RT&, RT&) const>(&RT::intersects)));
        }

        template<util::Arithmetic T>
        inline static void registerMatrixUserType(const std::string& name)
        {
                using MT = util::Matrix<T>;
                lua.new_usertype<MT>(name,
                        sol::constructors<
                                MT(const MT&),
                                MT(std::size_t, std::size_t),
                                MT(std::size_t, std::size_t, T),
                                MT(std::size_t, std::size_t, sol::table)
                        >{},
                        "get",  [](const MT& m, std::size_t r, std::size_t c)
                                {
                                        return m.get(r - 1, c - 1);
                                },
                        "set",  [](MT& m, std::size_t r, std::size_t c, T x)
                                {
                                        return m.set(r - 1, c - 1, x);
                                },
                        "rows", &MT::rows,
                        "columns", &MT::columns);
        }
}

inline static void loadMath()
{
        lua["clamp"]     = std::clamp<double>;
        lua["iclamp"]    = std::clamp<std::int32_t>;
        lua["lerp"]      = static_cast<double(*)(double, double, double)>(std::lerp);
        lua["normalize"] = util::normalize;
        lua["map"]       = util::map;

        impl::registerVectorUserType<float>("vec");
        impl::registerVectorUserType<std::int32_t>("ivec");
        impl::registerVectorUserType<std::uint32_t>("uvec");

        impl::registerRectangleUserType<float>("rect");
        impl::registerRectangleUserType<std::int32_t>("irect");
        impl::registerRectangleUserType<std::uint32_t>("urect");

        impl::registerMatrixUserType<float>("mat");
        impl::registerMatrixUserType<std::int32_t>("imat");
        impl::registerMatrixUserType<std::uint32_t>("umat");
}

}