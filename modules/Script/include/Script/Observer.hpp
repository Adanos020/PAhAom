#pragma once


#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>


namespace script
{

/** Broadcasts a PushState message from Lua to the Subject.
 * 
 *  Params:
 *      state = Table. Contains a string with the name of the state to push.
 */
inline lua::Retval pushState(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send({ util::Message::PushState{ context.args[0] } });
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