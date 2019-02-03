#include <PAhAom/GameState/GameState.hpp>
#include <PAhAom/Resources.hpp>
#include <PAhAom/Settings.hpp>

#include <util/Observer.hpp>

#include <iostream>

namespace PAhAom::GameState
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

void Game::update(const util::DeltaTime dt)
{

}

void Game::draw(sf::RenderTarget& target)
{
        target.draw(this->currentLevel);
}

}