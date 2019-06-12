#include <Engine/Engine.hpp>
#include <Engine/Resources.hpp>
#include <Engine/Settings.hpp>

#include <Util/Constants.hpp>
#include <Util/Random.hpp>
#include <Util/Types.hpp>

#include <Script.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
#include <iostream>


namespace engine
{

Engine::Engine()
{
        // Observer.
        util::Subject::addObserver(this);

        // RNG.
        util::rng.seed(std::chrono::system_clock::now().time_since_epoch().count());

        // Scripts.
        script::init();

        // Run if appropriate.
        if ((running = not scenes.empty()))
        {
                // Settings.
                Settings::Video::load();

                // Window setup.
                this->window.create(Settings::Video::videoMode(), "PAhAom", sf::Style::Close);
                this->window.setFramerateLimit(util::FPS);
                this->window.setKeyRepeatEnabled(false);

                // Render texture setup.
                const sf::Vector2u screenRes = Settings::Video::resolution;
                this->screenTexture.create(screenRes.x, screenRes.y);
                this->screen.setSize(sf::Vector2f(Settings::Video::windowSize));
                this->screen.setTexture(&this->screenTexture.getTexture());
        }
        else
        {
                std::cerr << util::err::noInitialState << std::endl;
        }
}

int Engine::run()
{
        if (not this->running)
        {
                return 1;
        }

        util::DeltaTime lag = 0.0;
        sf::Clock timer;

        while (this->running)
        {
                this->handleInput();
                while (lag >= util::FRAME_TIME)
                {
                        this->scenes.top().update();
                        lag -= util::FRAME_TIME;
                }
                this->draw();
                lag += timer.restart().asSeconds();
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
                this->scenes.top().handleInput(event);
        }
}

void Engine::draw()
{
        this->window.clear();

        this->screenTexture.clear();
        this->scenes.top().draw(screenTexture);
        this->screenTexture.display();

        this->window.draw(screen);
        this->window.display();
}

void Engine::receive(const util::Message& msg)
{
        if (auto val = std::get_if<util::Message::PushScene>(&msg.msg))
        {
                this->scenes.emplace(val->stateName);
        }
        else if (std::get_if<util::Message::PopScene>(&msg.msg))
        {
                if (this->scenes.size() > 1)
                {
                        util::Subject::deleteObserver(&this->scenes.top());
                        this->scenes.pop();
                }
                else
                {
                        this->running = false;
                }
        }
}

}

int main()
{
        return engine::Engine().run();
}