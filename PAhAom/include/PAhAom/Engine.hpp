#pragma once


#include <PAhAom/GameState/GameState.hpp>

#include <util/Observer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>
#include <stack>


namespace PAhAom
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

        std::stack<std::unique_ptr<GameState::State>> states;

        bool running;
};

}