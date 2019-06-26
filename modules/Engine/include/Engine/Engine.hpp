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

                this->running = true;
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
                                this->currentScene.update();
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
                        this->currentScene.handleInput(event);
                }
        }

        void draw()
        {
                this->window.clear();

                this->screenTexture.clear();
                this->currentScene.drawTo(screenTexture);
                this->screenTexture.display();

                this->window.draw(screen);
                this->window.display();
        }

private:
        
        virtual void receive(const util::Message& msg) override
        {
                std::visit(util::MsgHandlers {
                        [this](const util::Message::SwitchScene& msg)
                        {
                                this->currentScene.switchTo(msg.sceneName);
                        },
                        [this](const util::Message::Quit&)
                        {
                                this->running = false;
                        },
                        util::discardTheRest
                }, msg.msg);
        }

private:

        sf::RenderWindow window;
        sf::RenderTexture screenTexture;
        sf::RectangleShape screen;

        Scene currentScene;

        bool running;
};

}