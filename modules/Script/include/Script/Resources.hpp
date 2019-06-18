#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>


namespace script
{

template<typename T>
inline lua::Retval load(lua::Context& context)
{
        context.requireArgs<std::string, std::string>(2);
        return context.ret(engine::Resources<T>::load(context.args[0], context.args[1]));
}

template<typename T>
inline lua::Retval unload(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        return context.ret(engine::Resources<T>::unload(context.args[0]));
}

template<typename T>
inline lua::Retval unloadAll(lua::Context& context)
{
        engine::Resources<T>::unloadAll();
        return context.ret();
}

}