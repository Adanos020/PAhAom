#pragma once


#include <Script/Lua.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <algorithm>


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

        inline double lerp(double val1, double val2, double alpha)
        {
                return (1.0 - alpha) * val1 + alpha * val2;
        }

        inline double normalizeNumber(double val, double start, double stop)
        {
                return val / (stop - start);
        }

        inline double mapNumber(double val, double start1, double stop1, double start2, double stop2)
        {
                return normalizeNumber(val, start1, stop1) * (stop2 - start2) + start2;
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
                return context.ret(rect.contains(vec));
        }

        return context.ret();
}

inline lua::Retval clamp(lua::Context& context)
{
        context.requireArgs<double, double, double>(3);
        
        const lua::Valref val = context.args[0];
        const lua::Valref lo  = context.args[1];
        const lua::Valref hi  = context.args[2];

        if (val.isInteger() and lo.isInteger() and hi.isInteger())
        {
                return context.ret(std::clamp(val.to<int>(), lo.to<int>(), hi.to<int>()));
        }
        return context.ret(std::clamp(val.to<double>(), lo.to<double>(), hi.to<double>()));
}

inline lua::Retval lerp(lua::Context& context)
{
        context.requireArgs<double, double, double>(3);
        return context.ret(impl::lerp(context.args[0], context.args[1], context.args[2]));
}

inline lua::Retval normalizeNumber(lua::Context& context)
{
        context.requireArgs<double, double, double>(3);
        return context.ret(impl::normalizeNumber(context.args[0], context.args[1], context.args[2]));
}

inline lua::Retval mapNumber(lua::Context& context)
{
        context.requireArgs<double, double, double, double, double>(5);
        return context.ret(impl::mapNumber(context.args[0], context.args[1], context.args[2],
                                           context.args[3], context.args[4]));
}

}