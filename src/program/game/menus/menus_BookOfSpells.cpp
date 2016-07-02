/**
 * @file src/program/game/menus/menus_BookOfSpells.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "menus.hpp"

#include "../../program.hpp"

extern rr::Resources resources;
extern rr::Settings  settings;

namespace rr {

    BookOfSpells::BookOfSpells()
    : wBofs_(Window(resources.dictionary["gui.window.bookOfSpells"], sf::Vector2f(765, 470), (sf::Vector2f)settings.graphics.resolution/2.f - sf::Vector2f(382.5f, 235))) {

#define component(w, c, i) w.getComponent<c>(i)

        shadow_.setSize     ((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

            for (int i=0; i<3; i++) {
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(145, 100+100*i));
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(245, 100+100*i));
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(450, 100+100*i));
                wBofs_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(550, 100+100*i));
            }
            wBofs_+= new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
                component(wBofs_, Button, 0)->setPosition(sf::Vector2f(wBofs_.getPosition().x+wBofs_.getSize().x - component(wBofs_, Button, 0)->getSize().x-15,
                                                          	           settings.graphics.resolution.y/2+235      - component(wBofs_, Button, 0)->getSize().y-5));

#undef component

    }

    BookOfSpells::~BookOfSpells() {}

    void BookOfSpells::open() {
        wBofs_.setVisible(true);
    }

    void BookOfSpells::close() {
        wBofs_.setVisible(false);
    }

    void BookOfSpells::buttonEvents(sf::RenderWindow& rw, sf::Event& ev, Game* g) {

#define component(w, c, i) w.getComponent<c>(i)

        if (isOpen()) {
            if (  component(wBofs_, Button, 0)->isPressed(rw, ev)
                ) g->pause(false);

            for (int i=0; i<12; i++) {
                if (component(wBofs_, Slot, i)->isPressed(rw, ev)) {

                }
            }
        }

#undef component

    }

    void BookOfSpells::draw(sf::RenderWindow& rw) {
        if (isOpen()) {
            rw.draw(shadow_);
            wBofs_.draw(rw);
        }
    }

    bool BookOfSpells::isOpen() {
        return wBofs_.isVisible();
    }

}
