#include <Engine/Scene.hpp>

#include <Script/Lua.hpp>
#include <Script/Input.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

#include <Util/Math.hpp>
#include <Util/Constants.hpp>

namespace engine
{

Scene::Scene(const std::string& sceneName)
{
        this->switchTo(sceneName);
}

Scene::~Scene()
{
        this->destroy();
}

void Scene::destroy()
{
        this->systems.reset();
        script::lua[this->stateName] = sol::nil;
}

void Scene::switchTo(const std::string& sceneName)
{
        this->destroy();

        // Construct the scene object.
        sol::table classTable = script::lua[sceneName];
        script::lua[this->stateName] = classTable["new"](classTable);

        sol::table thisObj = script::lua[this->stateName];

        // Add predefined entities.
        sol::table entities = thisObj["entities"];
        entities.for_each([this](sol::object, sol::object el)
        {
                if (el.get_type() == sol::type::table)
                {
                        sol::table entity = el;
                        this->systems.addEntity(entity);
                }
        });
}

void Scene::load(const util::SceneID)
{
        this->destroy();
}

void Scene::save(util::SceneID id)
{
        if (!id)
        {
                id = ++currentId;
        }
}

void Scene::handleInput(const sf::Event& event)
{
        sol::table thisObj = script::lua[this->stateName];
        
        this->systems.input.handleInput(event);
        script::callInputHandler(thisObj, thisObj, event);
}

void Scene::update()
{
        sol::table thisObj = script::lua[this->stateName];
        thisObj["update"](thisObj, util::FRAME_TIME.asSeconds());
        this->systems.physics.update();
}

void Scene::drawTo(sf::RenderTarget& target)
{
        this->systems.render.drawTo(target);
}

util::SceneID Scene::nextId()
{
        return currentId + 1;
}

}