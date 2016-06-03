/**
 * @file src/program/game/messages/messages_Message.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "messages.hpp"
#include "../program.hpp"

extern rr::Resources resources;

namespace rr {

    Message::Message(sf::String text, sf::Color color, sf::Text::Style textStyle)
    : message_    (Text(text, resources.font.Unifont, 16, color, textStyle)),
      timeElapsed_(0),
      lifeTime_   (1500) {

        message_.wrap(400);
    }

    void Message::setPosition(sf::Vector2f position) {
        message_.setPosition(position);
    }

    void Message::update(float timeStep) {
        timeElapsed_ += timeStep;

        if (timeElapsed_ >= lifeTime_) {
            sf::Color newColor = message_.getColor();
            newColor.a -= 5;
            message_.setColor(newColor);
        }
    }

    void Message::draw(sf::RenderWindow& rw) {
        message_.draw(rw);
    }

}
