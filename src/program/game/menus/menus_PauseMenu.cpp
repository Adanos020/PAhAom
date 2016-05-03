/**
 * @file src/program/game/menus/menus_PauseMenu.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#include "menus.hpp"
#include "../../program.hpp"
#include "../../funcs/strings.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    PauseMenu::PauseMenu() {
        shadow.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow.setPosition(sf::Vector2f(0, 0));
        shadow.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)

        title = new Text(sf::Vector2f(0, 0), "PAhAom", resources.font.Pixel, 100, sf::Color::Yellow);
        title->setPosition(sf::Vector2f(settings.graphics.resolution.x/2-title->getSize().x/2, 10));

        wMenu = new Window("", sf::Vector2f(244, 230), sf::Vector2f(25, settings.graphics.resolution.y/2-153));
            *wMenu += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.resume" ], 52);
            *wMenu += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.help"   ], 52);
            *wMenu += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"   ], 52);
            for (int i=0; i<3; i++)
                component(wMenu, Button, i)->setPosition(wMenu->getPosition()+sf::Vector2f(wMenu->getSize().x/2-component(wMenu, Button, i)->getSize().x/2, 5+i*75));

            wMenu->addComponent(new Window(resources.dictionary["gui.button.help"], sf::Vector2f(325, 454),
                                           sf::Vector2f(settings.graphics.resolution.x-350, settings.graphics.resolution.y/2-225)), false);

#define wHelp component(wMenu, Window, 0)

                *wHelp += new Text(sf::Vector2f(20, 25), "Pro tip:",                                 resources.font.Unifont, 30, sf::Color::Yellow);
                *wHelp += new Text(sf::Vector2f(20, 55), resources.dictionary["gui.text.killurslf"], resources.font.Unifont, 30, sf::Color::Red);

                *wHelp += new Button(sf::Vector2f(5, 380), resources.dictionary["gui.button.quit"], 30);
                component(wHelp, Button, 0)->setPosition(sf::Vector2f(wHelp->getPosition().x+wHelp->getSize().x/2-component(wHelp, Button, 0)->getSize().x/2,
                                                                      wHelp->getPosition().y+wHelp->getSize().y-component(wHelp, Button, 0)->getSize().y-10));

#undef wHelp
#undef component

    }

    PauseMenu::~PauseMenu() {
        delete title;
        delete wMenu;
    }

    void PauseMenu::open() {
        wMenu->setVisible(true);
    }

    void PauseMenu::close() {

#define component(w, c, i) w->getComponent<c>(i)
#define wHelp component(wMenu, Window, 0)

        wMenu->setVisible(false);
        wHelp->setVisible(false);

#undef component
#undef wHelp

    }

    void PauseMenu::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)
#define wHelp component(wMenu, Window, 0)

        if (wMenu->isVisible()) {
            if (!wHelp->isVisible()) {
                if (component(wMenu, Button, 0)->isPressed(rw, e))
                    g->pause(false);
                if (component(wMenu, Button, 1)->isPressed(rw, e))
                    wHelp->setVisible(true);
                if (component(wMenu, Button, 2)->isPressed(rw, e)) {
                    g->pause(false);
                    g->start(false);
                }
            }

            else if (wHelp->isVisible()) {
                if (component(wHelp, Button, 0)->isPressed(rw, e))
                    wHelp->setVisible(false);
            }
        }

#undef component
#undef wHelp

        }

    void PauseMenu::draw(sf::RenderWindow& rw) {
        rw.draw(shadow);
        title->draw(rw);
        wMenu->draw(rw);
    }

    bool PauseMenu::isOpen() {
        return wMenu->isVisible();
    }

}
