#pragma once


#include <Script/Lua.hpp>

#include <Util/ErrorMessages.hpp>
#include <Util/Observer.hpp>


namespace script
{

/** Broadcasts a PushScene message from Lua to the Subject.
 * 
 *  Params:
 *      state = Table. Contains a string with the name of the state to push.
 */
inline lua::Retval pushScene(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send({ util::Message::PushScene{ context.args[0] } });
        return context.ret();
}

/** Broadcasts a PopScene message from Lua to the Subject.
 */
inline lua::Retval popScene(lua::Context& context)
{
        util::Subject::send({ util::Message::PopScene{} });
        return context.ret();
}

}