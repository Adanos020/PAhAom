#pragma once


#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Random.hpp>


namespace script
{

/** Chooses and returns either true or false, based on given probability. If there
 *  isn't a valid parameters given, the default value will be used.
 * 
 *  Params:
 *      prob (0.5) = Number in range from 0 to 1. The probability of returning true.
 * 
 *  Returns: Boolean
 */
inline lua::Retval chance(lua::Context& context)
{
        if (context.checkArgs<double>(1))
        {
                return context.ret(util::chance(context.args[0]));
        }
        return context.ret(util::chance());
}

/** Chooses and returns a number from a given uniformly distributed range. If there
 *  aren't two valid parameters given, an error will be raised.
 * 
 *  Params:
 *      lo = Number. Lower bound.
 *      hi = Number. Upper bound.
 * 
 *  Returns: Number
 */
inline lua::Retval uniform(lua::Context& context)
{
        context.requireArgs<double, double>(2);

        const lua::Value lo = context.args[0];
        const lua::Value hi = context.args[1];

        if (lo.isInteger() and hi.isInteger())
        {
                return context.ret(util::uniform(lo.to<int>(), hi.to<int>()));
        }
        return context.ret(util::uniform(lo.to<double>(), hi.to<double>()));
}

/** Chooses and returns a number from a given normally distributed range. If there
 *  aren't two valid parameters given, the default values will be used.
 * 
 *  Params:
 *      mean   (0) = Number. Mean.
 *      stddev (1) = Number. Standard deviation.
 * 
 *  Returns: Number
 */
inline lua::Retval normal(lua::Context& context)
{
        if (context.checkArgs<double, double>(2))
        {
                return context.ret(util::normal(context.args[0].to<double>(), context.args[1].to<double>()));
        }
        return context.ret(util::normal<double>());
}

}