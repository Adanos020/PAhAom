#pragma once


#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Random.hpp>


namespace script
{

lua::Retval chance(lua::Context& context)
{
        if (const lua::Value prob = context.args[0]; prob.is<double>())
        {
                return context.ret(util::chance(prob));
        }

        context.error(typeNotArithmetic);
        return context.ret();
}

lua::Retval uniform(lua::Context& context)
{
        const lua::Value lo = context.args[0];
        const lua::Value hi = context.args[1];

        if (lo.isInteger() and hi.isInteger())
        {
                return context.ret(util::uniform(lo.to<int>(), hi.to<int>()));
        }
        if (lo.is<double>() and hi.is<double>())
        {
                return context.ret(util::uniform(lo.to<double>(), hi.to<double>()));
        }

        context.error(typeNotArithmetic);
        return context.ret();
}

lua::Retval normal(lua::Context& context)
{
        if (context.args.empty())
        {
                return context.ret(util::normal<double>());
        }

        const lua::Value mean = context.args[0];
        const lua::Value stddev = context.args[1];

        if (mean.is<double>() and stddev.is<double>())
        {
                return context.ret(util::normal(mean.to<double>(), stddev.to<double>()));
        }

        context.error(typeNotFloatingPoint);
        return context.ret();
}

}