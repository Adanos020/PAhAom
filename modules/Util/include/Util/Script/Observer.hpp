#pragma once


#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>
#include <Util/Script/Script.hpp>

#include <iostream>


namespace util::script
{

/** Broadcasts a PushState message from Lua to the Subject.
 * 
 *  Its sole argument is a table containing a string containing the name of the state to push.
 */
inline auto pushState(lua::Context& context) -> lua::Retval
{
        if (lua::Value state = context.args.at(0); state.is<std::string>())
        {
                util::Subject::send({ util::Message::PushState{ state } });
        }
        else
        {
                std::cerr << util::err::noPushStateName() << std::endl;
        }

        return context.ret();
}

/** Broadcasts a PopState message from Lua to the Subject.
 */
inline auto popState(lua::Context& context) -> lua::Retval
{
        util::Subject::send({ util::Message::PopState{} });
        return context.ret();
}

}