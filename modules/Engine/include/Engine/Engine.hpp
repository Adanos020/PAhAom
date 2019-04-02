#pragma once


// #include <Engine/GameState/GameState.hpp>
#include <Engine/GameState.hpp>

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
        auto run() -> int;

private:

        auto handleInput() -> void;
        auto draw() -> void;
        
        virtual auto receive(const util::Message&) -> void override;

private:

        sf::RenderWindow window;
        sf::RenderTexture screenTexture;
        sf::RectangleShape screen;

        std::stack<GameState> states;

        bool running;
};

}