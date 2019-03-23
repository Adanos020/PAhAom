#include <Engine/GameState/GameState.hpp>
#include <Engine/Resources.hpp>
#include <Engine/Settings.hpp>

#include <Util/Observer.hpp>


namespace engine::GameState
{

Menu::Menu()
: text("Menu, press Enter to continue,\nEsc to exit.", *Resources::get<sf::Font>("unifont"))
{
        this->text.setPosition(sf::Vector2f(Settings::Video::resolution) / 2.f);
        this->text.setOrigin({ this->text.getGlobalBounds().width  / 2.f,
                               this->text.getGlobalBounds().height / 2.f });
}

void Menu::handleInput(const sf::Event& event)
{
        if (event.type == sf::Event::KeyPressed)
        {
                switch (event.key.code)
                {
                        case sf::Keyboard::Return:
                        {
                                util::Subject::send({ util::Message::PushState{ new Game() }});
                                break;
                        }

                        case sf::Keyboard::Escape:
                        {
                                util::Subject::send({ util::Message::PopState{}});
                                break;
                        }

                        default: break;
                }
        }
}

void Menu::update()
{

}

void Menu::draw(sf::RenderTarget& target)
{
        target.draw(this->text);
}

}