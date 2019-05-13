#pragma once


#include <Script/Lua.hpp>

#include <SFML/Graphics/Rect.hpp>


namespace script
{

namespace impl
{
        inline bool isVector(const lua::Table& vec)
        {
                return vec["x"].is<double>() and vec["y"].is<double>();
        }

        inline sf::Vector2f toVector(const lua::Table& vec)
        {
                return {vec["x"], vec["y"]};
        }

        inline bool vectorsEqual(const lua::Table& v1, const lua::Table& v2)
        {
                return v1["x"] == v2["x"] and v1["y"] == v2["y"];
        }

        inline bool isRectangle(const lua::Table& rect)
        {
                return isVector(rect["position"]) and isVector(rect["size"]);
        }

        inline sf::FloatRect toRectangle(const lua::Table& rect)
        {
                return {toVector(rect["position"]), toVector(rect["size"])};
        }
}

inline lua::Retval isVector(lua::Context& context)
{
        if (context.checkArgs<lua::Table>(1))
        {
                return context.ret(impl::isVector(context.args[0]));
        }
        return context.ret(false);
}

inline lua::Retval vectorsEqual(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        const lua::Table v1 = context.args[0];
        const lua::Table v2 = context.args[1];
        if (impl::isVector(v1) and impl::isVector(v2))
        {
                return context.ret(impl::vectorsEqual(v1, v2));
        }

        return context.ret(false);
}

inline lua::Retval isRectangle(lua::Context& context)
{
        if (context.checkArgs<lua::Table>(1))
        {
                return context.ret(impl::isRectangle(context.args[0]));
        }
        return context.ret(false);
}

inline lua::Retval rectanglesIntersect(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        const lua::Table t1 = context.args[0];
        const lua::Table t2 = context.args[1];
        if (impl::isRectangle(t1) and impl::isRectangle(t2))
        {
                const sf::FloatRect rect1 = impl::toRectangle(t1);
                const sf::FloatRect rect2 = impl::toRectangle(t2);
                return context.ret(rect1.intersects(rect2));
        }
        
        return context.ret();
}

inline lua::Retval rectangleContains(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::Table>(2);

        const lua::Table t1 = context.args[0];
        const lua::Table t2 = context.args[1];
        if (impl::isRectangle(t1) and impl::isVector(t2))
        {
                const sf::FloatRect rect = impl::toRectangle(t1);
                const sf::Vector2f vec = impl::toVector(t2);
                return context.ret(rect1.contains(vec));
        }

        return context.ret();
}

}