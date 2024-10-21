#pragma once

#include <Engine/Scene.hpp>

#include <Util/Observer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <cstdint>

namespace engine
{

class Engine : public util::Observer
{
public:
        Engine();

        int32_t run();

private:
        void handleInput();
        void draw();

private:
        virtual void receive(const util::Message& msg) override;

private:
        sf::RenderWindow window;
        sf::RenderTexture screenTexture;
        sf::RectangleShape screen;

        Scene currentScene;

        bool running;
};

}
