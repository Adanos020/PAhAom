#pragma once


#include <luapp.hpp>


namespace script
{

inline static lua::Retval tableAll(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::LFunction>(2);
        bool result = true;
        static_cast<lua::Table>(context.args[0]).iterate([&](lua::Valref, lua::Valref el)
        {
                if (not context.args[1](el))
                {
                        // If condition is met, break.
                        result = false;
                        return false;
                }
                // Otherwise continue.
                return true;
        });
        return context.ret(result);
}

inline static lua::Retval tableAny(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::LFunction>(2);
        bool result = false;
        static_cast<lua::Table>(context.args[0]).iterate([&](lua::Valref, lua::Valref el)
        {
                if (context.args[1](el))
                {
                        // If condition is met, break.
                        result = true;
                        return false;
                }
                // Otherwise continue.
                return true;
        });
        return context.ret(result);
}

inline static lua::Retval tableNone(lua::Context& context)
{
        context.requireArgs<lua::Table, lua::LFunction>(2);
        bool result = true;
        static_cast<lua::Table>(context.args[0]).iterate([&](lua::Valref, lua::Valref el)
        {
                if (context.args[1](el))
                {
                        // If condition is met, break.
                        result = false;
                        return false;
                }
                // Otherwise continue.
                return true;
        });
        return context.ret(result);
}

}