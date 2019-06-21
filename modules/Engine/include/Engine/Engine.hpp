#pragma once


#include <Engine/Scene.hpp>
#include <Engine/Settings.hpp>

#include <Util/Observer.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <chrono>
#include <cstdint>
#include <stack>


namespace engine
{

class Engine : public util::Observer
{
public:

        Engine()
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
                        this->screen.setSize(sf::Vector2f{Settings::Video::windowSize});
                        this->screen.setTexture(&this->screenTexture.getTexture());
                }
                else
                {
                        std::cerr << util::err::noInitialState << std::endl;
                }
        }

        std::int32_t run()
        {
                if (not this->running)
                {
                        return 1;
                }

                sf::Time lag;
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
                        lag += timer.restart();
                }
                this->window.close();

                return 0;
        }

private:

        void handleInput()
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

        void draw()
        {
                this->window.clear();

                this->screenTexture.clear();
                this->scenes.top().draw(screenTexture);
                this->screenTexture.display();

                this->window.draw(screen);
                this->window.display();
        }
        
        virtual void receive(const util::Message& msg) override
        {
                if (auto val = std::get_if<util::Message::PushScene>(&msg.msg))
                {
                        this->scenes.emplace(val->sceneName);
                }
                else if (std::get_if<util::Message::PopScene>(&msg.msg))
                {
                        if (this->scenes.size() > 1)
                        {
                                this->scenes.pop();
                        }
                        else
                        {
                                this->running = false;
                        }
                }
        }

private:

        sf::RenderWindow window;
        sf::RenderTexture screenTexture;
        sf::RectangleShape screen;

        std::stack<Scene> scenes;

        bool running;
};

}