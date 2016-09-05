/**
 * @file src/program/game/messages/Message.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "MessageManager.hpp"

#include "../Resources.hpp"

namespace rr
{

    Message::Message(sf::String text, sf::Color color, sf::Text::Style textStyle) :
      message_    (Text(text, Resources::font.Unifont, 16, color, textStyle)),
      timeElapsed_(sf::Time::Zero),
      lifeTime_   (sf::seconds(5))
    {
        message_.setOutlineColor(sf::Color::Black);
        message_.setOutlineThickness(1);
        message_.wrap(400);
    }

    void
    Message::setPosition(sf::Vector2f position)
    {
        message_.setPosition(position);
    }

    void
    Message::update(sf::Time timeStep)
    {
        timeElapsed_ += timeStep;

        if (timeElapsed_ >= lifeTime_)
        {
            sf::Color newColor = message_.getFillColor();
            newColor.a -= 5;
            message_.setFillColor(newColor);
        }
    }

    void
    Message::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(message_);
    }

}
