#include <Engine/Engine.hpp>
#include <Engine/Resources.hpp>
#include <Engine/Settings.hpp>

#include <Util/Constants.hpp>
#include <Util/Random.hpp>
#include <Util/Types.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
#include <iostream>


namespace engine
{

Engine::Engine()
: window ({Settings::Video::windowSize.x,
           Settings::Video::windowSize.y}, "PAhAom", sf::Style::Close)
, screen (sf::Vector2f(Settings::Video::windowSize))
, running (true)
{
        util::Subject::addObserver(this);

        // Window setup.
        this->window.setFramerateLimit(60);
        this->window.setKeyRepeatEnabled(false);

        // Render texture setup.
        const sf::Vector2u screenRes = Settings::Video::resolution;
        this->screenTexture.create(screenRes.x, screenRes.y);
        this->screen.setTexture(&this->screenTexture.getTexture());

        // State.
        this->states.emplace("Menu");
}

auto Engine::run() -> int
{
        util::DeltaTime lag = 0.0;

        sf::Clock timer;

        while (this->running)
        {
                lag += timer.restart().asSeconds();
                this->handleInput();

                while (lag >= util::FRAME_TIME)
                {
                        this->states.top().update();
                        lag -= util::FRAME_TIME;
                }

                this->draw();
        }
        this->window.close();

        return 0;
}

auto Engine::handleInput() -> void
{
        sf::Event event;
        while (this->window.pollEvent(event))
        {
                if (event.type == sf::Event::Closed)
                {
                        this->running = false;
                }
                this->states.top().handleInput(event);
        }
}

auto Engine::draw() -> void
{
        this->window.clear();

        this->screenTexture.clear();
        this->states.top().draw(screenTexture);
        this->screenTexture.display();

        this->window.draw(screen);
        this->window.display();
}

auto Engine::receive(const util::Message& msg) -> void
{
        if (auto val = std::get_if<util::Message::PushState>(&msg.msg))
        {
                this->states.emplace(val->stateName);
        }
        else if (std::get_if<util::Message::PopState>(&msg.msg))
        {
                if (this->states.size() > 1)
                {
                        this->states.pop();
                }
                else
                {
                        this->running = false;
                }
        }
}

}

auto init() -> bool
{
        // RNG
        util::Random::rng.seed(std::chrono::system_clock::now().time_since_epoch().count());

        // Scripts.
        util::luaState.runFile("data/script/init.lua");
        util::luaContext.global["push_state"] = util::script::pushState;
        util::luaContext.global["pop_state"] = util::script::popState;

        // Settings
        engine::Settings::Video::load();

        // Resources
        return engine::Resources::load<sf::Font>("unifont", "data/font/unifont.ttf") and
               engine::Resources::load<sf::Texture>("tileset", "data/graphics/tileset.png");
}

auto main() -> int
{
        if (not init())
        {
                std::cout << "Some resources could not be loaded." << std::endl;
                return 1;
        }

        return engine::Engine().run();
}