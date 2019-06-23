#pragma once


#include <Script/Lua.hpp>

#include <Util/Observer.hpp>


namespace script
{

/** Broadcasts a PushScene message from Lua to the Subject.
 * 
 *  Params:
 *      state = Table. Contains a string with the name of the state to push.
 */
[[deprecated]]
inline lua::Retval pushScene(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send(util::Message::PushScene{context.args[0]});
        return context.ret();
}

/** Broadcasts a PopScene message from Lua to the Subject.
 */
[[deprecated]]
inline lua::Retval popScene(lua::Context& context)
{
        util::Subject::send(util::Message::PopScene{});
        return context.ret();
}

/** Switches to another scene without saving the current scene.
 */
inline lua::Retval switchScene(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send(util::Message::SwitchScene{context.args[0]});
        return context.ret();
}

/** Switches to another scene and saves the current scene.
 */
inline lua::Retval saveAndSwitchScene(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send(util::Message::SaveAndSwitchScene{context.args[0]});
        return context.ret();
}

/** Loads another previously saved scene and switches to without saving
 *  the current scene.
 */
inline lua::Retval loadScene(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send(util::Message::LoadScene{context.args[0]});
        return context.ret();
}

/** Loads another previously saved scene, switches to it, and saves
 *  the current scene.
 */
inline lua::Retval saveAndLoadScene(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send(util::Message::SaveAndLoadScene{context.args[0]});
        return context.ret();
}

/** Terminates the program without saving the current scene.
 */
inline lua::Retval quit(lua::Context& context)
{
        util::Subject::send(util::Message::Quit{});
        return context.ret();
}

/** Terminates the program and saves the current scene.
 */
inline lua::Retval saveAndQuit(lua::Context& context)
{
        util::Subject::send(util::Message::SaveAndQuit{});
        return context.ret();
}

}