#pragma once


#include <Engine/Scene.hpp>

#include <Script/Lua.hpp>

#include <Util/Observer.hpp>


namespace script
{

/** Switches to another scene without saving the current scene.
 */
inline lua::Retval switchTo(lua::Context& context)
{
        context.requireArgs<std::string>(1);
        util::Subject::send(util::Message::SwitchScene{context.args[0]});
        return context.ret();
}

/** Saves the current scene. If a valid scene ID is given, an existing scene
 *  will be overwritten. Otherwise, the current scene will be saved in a new
 *  file.
 * 
 *  Returns: ID of the saved scene.
 */
inline lua::Retval saveScene(lua::Context& context)
{
        if (context.checkArgs<util::SceneID>(1))
        {
                util::Subject::send(util::Message::SaveScene{context.args[0]});
                return context.ret(context.args[0]);
        }
        util::Subject::send(util::Message::SaveScene{0});
        return context.ret(engine::Scene::nextId());
}

/** Loads another previously saved scene and switches to without saving
 *  the current scene.
 */
inline lua::Retval loadScene(lua::Context& context)
{
        context.requireArgs<util::SceneID>(1);
        util::Subject::send(util::Message::LoadScene{context.args[0]});
        return context.ret();
}

/** Terminates the program without saving the current scene.
 */
inline lua::Retval quit(lua::Context& context)
{
        util::Subject::send(util::Message::Quit{});
        return context.ret();
}

}