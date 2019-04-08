#pragma once


#include <Engine/Resources.hpp>

#include <Script/Lua.hpp>


namespace script
{

template<typename T>
inline lua::Retval load(lua::Context& context)
{
        if (lua::Value resource = context.args[0]; resource.is<std::string>())
        {
                if (lua::Value path = context.args[1]; resource.is<std::string>())
                {
                        return context.ret(engine::Resources::load<T>(resource, path));
                }
                context.error(util::err::noResourcePath);
                return context.ret(false);
        }

        context.error(util::err::noResourceName);
        return context.ret(false);
}

}