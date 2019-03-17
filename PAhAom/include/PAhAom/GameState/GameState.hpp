#pragma once


#include <PAhAom/Level/Level.hpp>

#include <util/Types.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>


namespace PAhAom::GameState
{

class State
{
public:

        virtual ~State() {}

        virtual void handleInput(const sf::Event& event) = 0;
        virtual void update() = 0;
        virtual void draw(sf::RenderTarget& target) = 0;
};


class Menu : public State
{
public:
        Menu();

        virtual void handleInput(const sf::Event&) override;
        virtual void update() override;
        virtual void draw(sf::RenderTarget&) override;

private:

        sf::Text text;
};


class Game : public State
{
public:
        Game();

        virtual void handleInput(const sf::Event&) override;
        virtual void update() override;
        virtual void draw(sf::RenderTarget&) override;

private:

        Level::DungeonGenerator<Level::MAP_WIDTH, Level::MAP_HEIGHT> dungeonGen;
        Level::Level<Level::MAP_WIDTH, Level::MAP_HEIGHT> currentLevel;
};

}