#include <Engine/GameState/GameState.hpp>
#include <Engine/Resources.hpp>
#include <Engine/Settings.hpp>

#include <Util/Observer.hpp>

#include <iostream>

namespace engine::GameState
{

Game::Game()
: currentLevel(dungeonGen)
{
        this->currentLevel.setPosition({8.f, 12.f});
}

void Game::handleInput(const sf::Event& event)
{
        if (event.type == sf::Event::KeyPressed)
        {
                switch (event.key.code)
                {
                        case sf::Keyboard::Escape:
                        {
                                util::Subject::send({ util::Message::PopState{} });
                                break;
                        }

                        default: break;
                }
        }
}

void Game::update()
{

}

void Game::draw(sf::RenderTarget& target)
{
        target.draw(this->currentLevel);
}

}