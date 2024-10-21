#include <Engine/Engine.hpp>

#include <Engine/Settings.hpp>

#include <Script.hpp>

#include <Util/Constants.hpp>
#include <Util/Random.hpp>

#include <chrono>

namespace engine
{

Engine::Engine()
{
        // Observer.
        util::Subject::addObserver(this);

        // RNG.
        util::rng.seed(std::chrono::system_clock::now().time_since_epoch().count());

        // Scripts.
        script::init(this->window);

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

int32_t Engine::run()
{
        if (!this->running)
        {
                return EXIT_FAILURE;
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

        return EXIT_SUCCESS;
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
                this->currentScene.handleInput(event);
        }
}

void Engine::draw()
{
        this->window.clear();

        this->screenTexture.clear();
        this->currentScene.drawTo(screenTexture);
        this->screenTexture.display();

        this->window.draw(screen);
        this->window.display();
}

void Engine::receive(const util::Message& msg)
{
        std::visit(util::MsgHandlers {
                [this](const util::Message::SwitchScene& msg)
                {
                        this->currentScene.switchTo(msg.sceneName);
                },
                [this](const util::Message::SaveScene& msg)
                {
                        this->currentScene.save(msg.sceneId);
                },
                [this](const util::Message::LoadScene& msg)
                {
                        this->currentScene.load(msg.sceneId);
                },
                [this](const util::Message::Quit&)
                {
                        this->running = false;
                },
                util::discardTheRest
        }, msg.msg);
}

}
