#pragma once


#include <Engine/Scene.hpp>

#include <Script/Lua.hpp>

#include <Util/Observer.hpp>


namespace script
{

/** Switches to another scene without saving the current scene.
 * 
 *  Params:
 *      sceneName = String. Name of the scene type.
 */
inline static void switchTo(const std::string& sceneName)
{
        util::Subject::send(util::Message::SwitchScene{sceneName});
}

/** Saves the current scene. If a valid scene ID is given, an existing scene
 *  will be overwritten. Otherwise, the current scene will be saved in a new
 *  file.
 * 
 *  Params:
 *      id (0) = Number. ID of the scene to overwrite. If 0 is given, a new
 *               scene record is created.
 * 
 *  Returns: ID of the saved scene.
 */
inline static util::SceneID saveScene(const util::SceneID id = 0)
{
        util::Subject::send(util::Message::SaveScene{id});
        return id ? id : engine::Scene::nextId();
}

/** Loads another previously saved scene and switches to without saving
 *  the current scene.
 * 
 *  Params:
 *      id (0) = Number. ID of the scene to load.
 */
inline static void loadScene(const util::SceneID id)
{
        util::Subject::send(util::Message::LoadScene{id});
}

/** Terminates the program.
 */
inline static void quit()
{
        util::Subject::send(util::Message::Quit{});
}

inline static void loadScenes()
{
        lua["game"] = lua.create_table_with(
                "switchTo",  switchTo,
                "saveScene", saveScene,
                "loadScene", loadScene,
                "quit",      quit);
}

}