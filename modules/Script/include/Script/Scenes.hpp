#pragma once

#include <Engine/Scene.hpp>

namespace script
{

/** Switches to another scene without saving the current scene.
 * 
 *  Params:
 *      sceneName = String. Name of the scene type.
 */
void switchTo(const std::string& sceneName);

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
util::SceneID saveScene(const util::SceneID id = 0);

/** Loads another previously saved scene and switches to without saving
 *  the current scene.
 * 
 *  Params:
 *      id (0) = Number. ID of the scene to load.
 */
void loadScene(const util::SceneID id = 0);

/** Terminates the program.
 */
void quit();

void loadScenes();

}
