#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>

#include <lua.hpp>

#include <iostream>


namespace util::script
{

/** Broadcasts a message from Lua to the Subject.
 */
inline auto broadcast(lua::Context& context) -> lua::Retval
{
        const lua::Table msg = context.args.at(0);

        lua::Value type = msg["type"];
        if (type.type() != lua::ValueType::String)
        {
                std::cerr << util::err::noMessageTypeId() << std::endl;
        }

        if (type == "PushState")
        {
                if (lua::Value state = msg["state"]; state.type() == lua::ValueType::String)
                {
                        util::Subject::send({ util::Message::PushState{ state } });
                }
                else
                {
                        std::cerr << util::err::noPushStateName() << std::endl;
                }
        }
        else if (type == "PopState")
        {
                util::Subject::send({ util::Message::PopState{} });
        }

        return context.ret();
}

}