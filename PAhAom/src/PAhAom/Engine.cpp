#include <PAhAom/Engine.hpp>
#include <PAhAom/Resources.hpp>
#include <PAhAom/Settings.hpp>

#include <util/Constants.hpp>
#include <util/Random.hpp>
#include <util/Types.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
#include <iostream>


namespace PAhAom
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
        this->states.emplace(new GameState::Menu());
}

int Engine::run()
{
        util::DeltaTime lag = 0.0;

        sf::Clock timer;

        while (this->running)
        {
                lag += timer.restart().asSeconds();
                this->handleInput();

                while (lag >= util::FRAME_TIME)
                {
                        this->states.top()->update();
                        lag -= util::FRAME_TIME;
                }

                this->draw();
        }
        this->window.close();

        return 0;
}

void Engine::handleInput()
{
        sf::Event event;
        while (this->window.pollEvent(event))
        {
                if (event.type == sf::Event::Closed)
                {
                        this->running = false;
                }
                this->states.top()->handleInput(event);
        }
}

void Engine::draw()
{
        this->window.clear();

        this->screenTexture.clear();
        this->states.top()->draw(screenTexture);
        this->screenTexture.display();

        this->window.draw(screen);
        this->window.display();
}

void Engine::receive(const util::Message& msg)
{
        if (auto val = std::get_if<util::Message::PushState>(&msg.msg))
        {
                this->states.emplace(val->state);
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

bool init()
{
        // RNG
        util::Random::rng.seed(std::chrono::system_clock::now().time_since_epoch().count());

        // Settings
        PAhAom::Settings::Video::load("settings.cfg");

        // Resources
        return PAhAom::Resources::load<sf::Font>("unifont", "data/font/unifont.ttf") and
               PAhAom::Resources::load<sf::Texture>("tileset", "data/graphics/tileset.png");
}

int main()
{
        if (not init())
        {
                std::cout << "Some resources could not be loaded." << std::endl;
                return 1;
        }

        return PAhAom::Engine().run();
}