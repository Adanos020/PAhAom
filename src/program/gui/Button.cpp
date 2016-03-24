#include "gui.h"

namespace rr {

    Button::Button(sf::Vector2f position, std::string str, unsigned chsize, sf::Color c) :Component() {
        text = new Text(str, chsize, c);
        text->setPosition(sf::Vector2f(position.x+15, position.y-0.5));

        image = new Image(position, 14, "data/graphics/gui.png", 0);

        body.setPosition(position);
        body.setSize(sf::Vector2f(text->getSize().x+20, text->getSize().y*2.1));
        body.setFillColor(sf::Color(0, 0, 0));
    }

    Button::Button(sf::Vector2f position, std::wstring str, unsigned chsize, sf::Color c) :Component() {
        text = new Text(str, chsize, c);
        text->setPosition(sf::Vector2f(position.x+15, position.y-0.5));

        image = new Image(position, 14, "data/graphics/gui.png", 0);

        body.setPosition(position);
        body.setSize(sf::Vector2f(text->getSize().x+20, text->getSize().y*2.1));
        body.setFillColor(sf::Color(0, 0, 0));
    }

    Button::~Button() {
        delete text;
    }

    bool Button::containsMouseCursor(sf::RenderWindow& rw) {
        if (body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(rw))) {
            body.setFillColor(sf::Color(128, 128, 128, 255));
            return true;
        }
        body.setFillColor(sf::Color(128, 128, 128, 128));
        return false;
    }

    void Button::setPosition(sf::Vector2f position) {
        body.setPosition(position);
        text->setPosition(sf::Vector2f(position.x+10, position.y-0.5));
        image->setPosition(position);
    }

    Text* Button::getText() {
        return text;
    }

    sf::Vector2f Button::getPosition() {
        return body.getPosition();
    }

    sf::Vector2f Button::getSize() {
        return body.getSize();
    }

    void Button::draw(sf::RenderWindow& rw) {
        rw.draw(body);
        text->draw(rw);
    }

}
