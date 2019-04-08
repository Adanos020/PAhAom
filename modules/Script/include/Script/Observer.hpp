#pragma once


#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>


namespace script
{

/** Broadcasts a PushState message from Lua to the Subject.
 * 
 *  Its sole argument is a table containing a string containing the name of the state to push.
 */
inline lua::Retval pushState(lua::Context& context)
{
        if (lua::Value state = context.args[0]; state.is<std::string>())
        {
                util::Subject::send({ util::Message::PushState{ state } });
        }
        else
        {
                context.error(util::err::noPushStateName);
        }

        return context.ret();
}

/** Broadcasts a PopState message from Lua to the Subject.
 */
inline lua::Retval popState(lua::Context& context)
{
        util::Subject::send({ util::Message::PopState{} });
        return context.ret();
}

}