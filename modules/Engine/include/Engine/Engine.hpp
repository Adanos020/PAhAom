#pragma once


#include <Engine/Scene.hpp>

#include <Util/Observer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>
#include <stack>


namespace engine
{

class Engine : public util::Observer
{
public:

        Engine();
        int run();

private:

        void handleInput();
        void draw();
        
        virtual void receive(const util::Message&) override;

private:

        sf::RenderWindow window;
        sf::RenderTexture screenTexture;
        sf::RectangleShape screen;

        std::stack<Scene> scenes;

        bool running;
};

}