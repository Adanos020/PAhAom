#pragma once

#include <Engine/ECS/Systems.hpp>

#include <Util/Types.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <string>

namespace engine
{

class Scene
{
public:
        Scene() = default;
        Scene(const std::string& sceneName);
        ~Scene();

        void destroy();
        void switchTo(const std::string& sceneName);
        void load(const util::SceneID);
        void save(util::SceneID id);
        void handleInput(const sf::Event& event);
        void update();
        void drawTo(sf::RenderTarget& target);

public:
        static util::SceneID nextId();

private:
        inline static util::SceneID currentId = 0;

        std::string stateName;
        ecs::Systems systems;
};

}
