#pragma once


#include <Engine/Resources.hpp>

#include <Util/Script.hpp>


namespace util::script
{

template<typename T>
inline auto load(lua::Context& context) -> lua::Retval
{
        if (lua::Value resource = context.args.at(0); resource.is<std::string>())
        {
                if (lua::Value path = context.args.at(1); resource.is<std::string>())
                {
                        return context.ret(engine::Resources::load<T>(resource, path));
                }
                std::cerr << util::err::noResourcePath() << std::endl;
                return context.ret(false);
        }

        std::cerr << util::err::noResourceName() << std::endl;
        return context.ret(false);
}

}