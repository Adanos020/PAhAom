#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>
#include <Util/Script.hpp>

#include <iostream>


namespace util::script
{

/** Broadcasts a message from Lua to the Subject.
 * 
 *  Its sole argument is a table containing a string (message type) and other parameters
 *  relevant to that type of message.
 */
inline auto pushState(lua::Context& context) -> lua::Retval
{
        if (lua::Value state = context.args.at(0); state.type() == lua::ValueType::String)
        {
                util::Subject::send({ util::Message::PushState{ state } });
        }
        else
        {
                std::cerr << util::err::noPushStateName() << std::endl;
        }

        return context.ret();
}

/** Broadcasts a message from Lua to the Subject.
 * 
 *  Its sole argument is a table containing a string (message type) and other parameters
 *  relevant to that type of message.
 */
inline auto popState(lua::Context& context) -> lua::Retval
{
        util::Subject::send({ util::Message::PopState{} });
        return context.ret();
}

}