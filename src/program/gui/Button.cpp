/**
 * @file src/program/gui/Button.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "Button.hpp"

#include "../Resources.hpp"

namespace rr
{

    Button::Button(sf::Vector2f position, sf::String str, unsigned chsize, sf::Color c) :
      image_(Image(position, Resources::texture.gui, 14, 0)),
      text_ (Text (sf::Vector2f(0, 0), str, Resources::font.Unifont, chsize, c)),
      held_ (false)
    {
        text_ .setParentComponent(this);

        image_.setParentComponent(this);

        body_ .setPosition        (position);
        body_ .setSize            (sf::Vector2f(text_.getSize().x+25, chsize*1.3425));
        body_ .setFillColor       (sf::Color(0, 0, 0));
        body_ .setOutlineColor    (sf::Color::Black);
        body_ .setOutlineThickness((float) chsize/20.f);

        text_ .setPosition        (sf::Vector2f(position.x + body_.getSize().x/2 - text_.getSize().x/2 - chsize/20,
                                                position.y-0.5));
    }

    void
    Button::setText(sf::String s)
    {
        text_.setString(s);
        body_.setSize     (sf::Vector2f(text_.getSize().x+25, text_.getCharacterSize()*1.3425));
        body_.setFillColor(sf::Color(0, 0, 0));

        text_.setPosition (sf::Vector2f(body_.getPosition().x + body_.getSize().x/2 - text_.getSize().x/2 - text_.getCharacterSize()/20,
                                        body_.getPosition().y-0.5));
    }

    bool
    Button::containsMouseCursor(sf::RenderWindow& rw)
    {
        if (body_.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw)))
        {
            body_.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body_.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    bool
    Button::isPressed(sf::RenderWindow& rw, sf::Event& e)
    {
        if (containsMouseCursor(rw) && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
        {
            held_ = true;
            return true;
        }
        if (  e.type == sf::Event::MouseButtonReleased
            ) held_ = false;
        return false;
    }

    void
    Button::setPosition(sf::Vector2f position)
    {
        body_ .setPosition(position);
        text_ .setPosition(sf::Vector2f(position.x+body_.getSize().x/2-text_.getSize().x/2-text_.getCharacterSize()/20, position.y-0.5));
        image_.setPosition(position);
    }

    void
    Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(body_ , states);
        target.draw(text_ , states);
        target.draw(image_, states);
    }

}
