/**
 * @file src/program/menus_Inventory.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "menus.hpp"
#include "../../program.hpp"

extern rr::Settings  settings;
extern rr::Resources resources;

namespace rr {

    Inventory::Inventory() {
        bronze_ = 0;
        silver_ = 0;
        gold_   = 0;

        shadow_.setSize((sf::Vector2f)settings.graphics.resolution);
        shadow_.setPosition(sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w->getComponent<c>(i)
#define wInfo component(wInve_, Window, 0)

        wInve_ = new Window(resources.dictionary["gui.window.inventory"], sf::Vector2f(765, 470), (sf::Vector2f)(settings.graphics.resolution/2u-sf::Vector2u(382, 225)));
            for (int i=0; i<4; i++) {
                for (int j=0; j<8; j++) {
                    *wInve_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(10+j*95, 30+i*95));
                }
            }

            *wInve_ += new Image (sf::Vector2f(0  , 390), resources.texture.items, 16, 33);
            *wInve_ += new Image (sf::Vector2f(150, 390), resources.texture.items, 16, 34);
            *wInve_ += new Image (sf::Vector2f(300, 390), resources.texture.items, 16, 35);

            *wInve_ += new Text  (sf::Vector2f(70 , 415), "GOLD", resources.font.Pixel, 30);
            *wInve_ += new Text  (sf::Vector2f(220, 415), "SILV", resources.font.Pixel, 30);
            *wInve_ += new Text  (sf::Vector2f(370, 415), "BRON", resources.font.Pixel, 30);

            *wInve_ += new Button(sf::Vector2f(0, 0), resources.dictionary["gui.button.quit"], 30);
                component(wInve_, Button, 0)->setPosition(sf::Vector2f(wInve_->getPosition().x+wInve_->getSize().x-component(wInve_, Button, 0)->getSize().x-15, settings.graphics.resolution.y/2+235-component(wInve_, Button, 0)->getSize().y-5));

            *wInve_ += new Window("", sf::Vector2f(410, 40), sf::Vector2f(0, 0));
                *wInfo += new Text(sf::Vector2f(5, 20), "", resources.font.Unifont, 20);
                component(wInfo, Text, 0)->setStyle(sf::Text::Regular);

#undef component
#undef wInfo

    }

    Inventory::~Inventory() {
        delete wInve_;
    }

    void Inventory::open() {
        wInve_->getComponent<Text>(0)->setString(std::to_string((int)gold_));
        wInve_->getComponent<Text>(1)->setString(std::to_string((int)silver_));
        wInve_->getComponent<Text>(2)->setString(std::to_string((int)bronze_));

        wInve_->setVisible(true);
    }

    void Inventory::close() {
        wInve_->setVisible(false);
    }

    void Inventory::clear() {
        for (int i=0; i<32; i++) {
            wInve_->getComponent<Slot>(i)->clear();
        }
        gold_   = 0;
        silver_ = 0;
        bronze_ = 0;
    }

    void Inventory::draw(sf::RenderWindow& rw) {
        rw.draw(shadow_);
        wInve_->draw(rw);
    }

    bool Inventory::isOpen() {
        return wInve_->isVisible();
    }

    void Inventory::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* g) {

#define component(w, c, i) w->getComponent<c>(i)
#define wInfo component(wInve_, Window, 0)

        if (wInve_->isVisible()) {
            if (component(wInve_, Button, 0)->isPressed(rw, e))
                g->pause(false);

            bool slotPointed = false;
            for (int i=0; i<32; i++) {
                if (component(wInve_, Slot, i)->containsMouseCursor(rw) && !component(wInve_, Slot, i)->isEmpty()) {
                    if (component(wInve_, Slot, i)->isPressed(rw, e) && !component(wInve_, Slot, i)->isEmpty()) {
                        g->getPlayer()->useItem(component(wInve_, Slot, i)->getItem());
                        if (component(wInve_, Slot, i)->getItem()->isDisposable())
                            component(wInve_, Slot, i)->removeItem(1);
                    }
                    else {
                        wInfo->setParentComponent(component(wInve_, Slot, i));
                        slotPointed = true;
                    }
                }
            }
            if (slotPointed) {
                component(wInfo, Text, 0)->setString(((Slot*)wInfo->getParentComponent())->getItem()->getDescription());
                component(wInfo, Text, 0)->wrap     ((wInfo->getText()->getSize().x>=300.f) ? wInfo->getText()->getSize().x+10 : 300.f);

                wInfo->setTitle(((Slot*)wInfo->getParentComponent())->getItem()->getName());
                wInfo->setSize(component(wInfo, Text, 0)->getSize()+sf::Vector2f(10, 30));
                wInfo->setPosition((sf::Vector2f)sf::Mouse::getPosition(rw)+sf::Vector2f(5, 5));

                if (wInfo->getPosition().x+wInfo->getSize().x+5 > (float)rw.getSize().x)
                    wInfo->setPosition((sf::Vector2f)sf::Mouse::getPosition(rw)-sf::Vector2f(wInfo->getPosition().x+wInfo->getSize().x-(float)rw.getSize().x, -5));
                if (wInfo->getPosition().y+wInfo->getSize().y+5 > (float)rw.getSize().y)
                    wInfo->setPosition((sf::Vector2f)sf::Mouse::getPosition(rw)-sf::Vector2f(-5, wInfo->getPosition().y+wInfo->getSize().y-(float)rw.getSize().y));

                wInfo->setVisible(true);
            }
            else
                wInfo->setVisible(false);
        }

#undef component
#undef wInfo

    }

    bool Inventory::addItem(Item* item) {

#define slot(i) wInve_->getComponent<Slot>(i)

     // in the beginning we check if the picked item is a coin
        if (instanceof<Coin, Item>(item)) {
         // first we recognize the coin type and size
            if (((Coin*)item)->type_ == Coin::BRONZE) {
                if (((Coin*)item)->size_ == Coin::BIG)
                    bronze_ += item->getAmount()*10;
                else
                    bronze_ += item->getAmount();
            }
            else if (((Coin*)item)->type_ == Coin::SILVER) {
                if (((Coin*)item)->size_ == Coin::BIG)
                    silver_ += item->getAmount()*10;
                else
                    silver_ += item->getAmount();
            }
            else if (((Coin*)item)->type_ == Coin::GOLDEN) {
                if (((Coin*)item)->size_ == Coin::BIG)
                    gold_ += item->getAmount()*10;
                else
                    gold_ += item->getAmount();
            }
         // then we do the simple calculations: 1 gold = 100 silver, 1 silver = 100 bronze
            while (bronze_ >= 50) {
                bronze_ -= 50;
                silver_++;
            }
            while (silver_ >= 50) {
                silver_ -= 50;
                gold_++;
            }
         // and in the end we can just:
            return true;
        }

     // if the item we want to add is stackable then we check if any of the slots already contains it
        if (item->isStackable()) {
            for (int it=0; it<32; it++) {
                if (!slot(it)->isEmpty() && slot(it)->getItem()->getID() == item->getID()) {
                    return slot(it)->addItem(item);
                }
            }
        }

     // if not then we look for the first empty slot and add the item to it
        for (int it=0; it<32; it++) {
            if (slot(it)->isEmpty()) {
                return slot(it)->addItem(item);
            }
        }

     // if there is no empty slot, we just exit the function
        return false;

#undef slot

    }

}
