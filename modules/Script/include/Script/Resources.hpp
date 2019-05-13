#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>


namespace script
{

template<typename T>
inline lua::Retval load(lua::Context& context)
{
        context.requireArgs<std::string, std::string>(2);
        return context.ret(engine::Resources::load<T>(context.args[0], context.args[1]));
}

}