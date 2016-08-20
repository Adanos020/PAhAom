/**
 * @file src/program/game/ui/Inventory.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Inventory.hpp"

#include "../../gui/Button.hpp"
#include "../../gui/Image.hpp"
#include "../../gui/Menu.hpp"
#include "../../gui/Text.hpp"

#include "../../Resources.hpp"
#include "../../Settings.hpp"

#include "../../funcs/files.hpp"

extern rr::Subject subject;

namespace rr {

    Inventory::Inventory(Player* p) :
      wInve_  (Window(Resources::dictionary["gui.window.inventory"], sf::Vector2f(765, 470), (sf::Vector2f) (Settings::graphics.resolution/2u - sf::Vector2u(382, 225)))),
      player_ (p),
      bronze_ (0),
      silver_ (0),
      gold_   (0)
    {
        shadow_.setSize     ((sf::Vector2f) Settings::graphics.resolution);
        shadow_.setPosition (sf::Vector2f(0, 0));
        shadow_.setFillColor(sf::Color(0, 0, 0, 172));

#define component(w, c, i) w.getComponent<c>(i)

            for (int i=0; i<4; ++i) {
                for (int j=0; j<8; ++j) {
                    wInve_ += new Slot(sf::Vector2f(80, 80), sf::Vector2f(10 + j*95, 30 + i*95));
                }
            }

            wInve_ += new Image (sf::Vector2f(0  , 390), Resources::texture.items, 16, 33);
            wInve_ += new Image (sf::Vector2f(150, 390), Resources::texture.items, 16, 34);
            wInve_ += new Image (sf::Vector2f(300, 390), Resources::texture.items, 16, 35);

            wInve_ += new Text  (sf::Vector2f(70 , 415), "GOLD", Resources::font.Pixel, 30);
            wInve_ += new Text  (sf::Vector2f(220, 415), "SILV", Resources::font.Pixel, 30);
            wInve_ += new Text  (sf::Vector2f(370, 415), "BRON", Resources::font.Pixel, 30);

            auto bQuit = new Button(sf::Vector2f(0, 0), Resources::dictionary["gui.button.quit"], 30);
                 bQuit->setPosition(sf::Vector2f(wInve_.getSize().x - bQuit->getSize().x - 15, 
                                                 wInve_.getSize().y - bQuit->getSize().y -  5));

            auto wInfo = new Window("", sf::Vector2f(410, 40), sf::Vector2f(0, 0)); {
                auto tDescription = new Text(sf::Vector2f(5, 20), "", Resources::font.Unifont, 20);
                	 tDescription->setStyle(sf::Text::Regular);
                     tDescription->setOutlineColor(sf::Color(0x40, 0x40, 0x40));
                *wInfo += tDescription;
            }
            auto wOpts = new Window("", sf::Vector2f(142, 143), sf::Vector2f(0, 0)); {
                 auto mOpts = new Menu(sf::Vector2f(5, 25));
                      mOpts->addOption(Resources::dictionary["gui.menu.use"            ]);
                      mOpts->addOption(Resources::dictionary["gui.menu.move_to_carryon"]);
                      mOpts->addOption(Resources::dictionary["gui.menu.drop"           ]);
                 *wOpts += mOpts;
            }

            ((wInve_ |= wInfo) |= wOpts) += bQuit;

        for (int i=0; i<5; ++i) {
            sCarryOn_[i] = new Slot(sf::Vector2f(80, 80), sf::Vector2f(Settings::graphics.resolution.x-90, Settings::graphics.resolution.y/2-250 + i*95));
        }

#undef component

    }

    Inventory::~Inventory() {
        for (auto slot : sCarryOn_) {
            delete slot;
        }
    }

    void Inventory::clear() {
        for (int i=0; i<32; ++i) {
            wInve_.getComponent<Slot>(i)->clear();
        }
        for (auto slot : sCarryOn_) {
            slot->clear();
        }
        gold_   = 0;
        silver_ = 0;
        bronze_ = 0;
    }

    void Inventory::buttonEvents(sf::RenderWindow& rw, sf::Event& e, Game* game) {

#define component(w, c, i) w.getComponent<c>(i)
#define wInfo (*component(wInve_, Window, 0))
#define wOpts (*component(wInve_, Window, 1))
;

        if (wInve_.isVisible()) {
            if (wOpts.isVisible()) { // ITEM OPTIONS WINDOW IS OPEN
                sf::String chosenOption = component(wOpts, Menu, 0)->getChosenOption(rw, e);
                if (chosenOption == Resources::dictionary["gui.menu.use"]) {
                    Item* item = ((Slot*)wOpts.getParentComponent())->getItem();

                    if (instanceof<Equipable, Item>(item)) {
                        bool equip = !((Equipable*)item)->isEquipped(); 
                        
                        if (  player_->equipItem((Equipable*)item, equip)
                            ) ((Equipable*)item)->equip(equip);
                        
                        if (instanceof<ColdWeapon, Item>(item)) {
                            for (int i=0; i<32; ++i) {
                                if (instanceof <ColdWeapon, Item> (component(wInve_, Slot, i)->getItem())) {
                                    ((Equipable*)component(wInve_, Slot, i)->getItem())->equip(false);
                                }
                            }
                        }
                    }
                    else {
                        game->getPlayer()->useItem(item);
                        if (item->isDisposable()) {
                            ((Slot*)wOpts.getParentComponent())->removeItem(1);
                            sort();
                        }
                    }
                }
                else if (chosenOption == Resources::dictionary["gui.menu.drop"]) {
                    Item* item = ((Slot*)wOpts.getParentComponent())->getItem();
                    item->setPosition(player_->getPosition());

                    if (  instanceof<Equipable, Item>(item)
                       && ((Equipable*)item)->isEquipped()
                        ) ((Equipable*)item)->equip(false);
                    
                    subject.notify(Observer::ITEM_DROPPED, item);
                    
                    ((Slot*)wOpts.getParentComponent())->removeItem(false);
                    sort();
                }
                else if (chosenOption == Resources::dictionary["gui.menu.to_carryon"]) {

                }

                if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button != sf::Mouse::Middle) {
                    wOpts.setParentComponent(nullptr);
                    wOpts.setVisible(false);
                }
            }
            else { // ITEM OPTIONS WINDOW IS NOT OPEN
                if (  component(wInve_, Button, 0)->isPressed(rw, e)
                    ) game->pause(false);

                bool slotPointed = false;
                /* BACKPACK */
                for (int i=0; i<32; ++i) {
                    if (   component(wInve_, Slot, i)->containsMouseCursor(rw)
                       && !component(wInve_, Slot, i)->isEmpty()
                        ) {
                        // SLOT WAS LEFT-CLICKED
                        if (   component(wInve_, Slot, i)->isPressed(rw, e)
                           && !component(wInve_, Slot, i)->isEmpty()
                            ) {
                            if (instanceof<Equipable, Item>(component(wInve_, Slot, i)->getItem())) {
                                bool equip = !((Equipable*)component(wInve_, Slot, i)->getItem())->isEquipped(); 
                                
                                if (  player_->equipItem((Equipable*) component(wInve_, Slot, i)->getItem(), equip)
                                    ) ((Equipable*)component(wInve_, Slot, i)->getItem())->equip(equip);

                                if (instanceof<ColdWeapon, Item>(component(wInve_, Slot, i)->getItem())) {
                                    for (int j=0; j<32; ++j) {
                                        if (j != i && instanceof <ColdWeapon, Item> (component(wInve_, Slot, j)->getItem())) {
                                            ((Equipable*) component(wInve_, Slot, j)->getItem())->equip(false);
                                        }
                                    }
                                }

                                if (instanceof<RangedWeapon, Item>(component(wInve_, Slot, i)->getItem())) {
                                    for (int j=0; j<32; ++j) {
                                        if (j != i && instanceof <RangedWeapon, Item> (component(wInve_, Slot, j)->getItem())) {
                                            ((Equipable*) component(wInve_, Slot, j)->getItem())->equip(false);
                                        }
                                    }
                                }
                            }
                            else {
                                game->getPlayer()->useItem(component(wInve_, Slot, i)->getItem());
                                if (component(wInve_, Slot, i)->getItem()->isDisposable()) {
                                    component(wInve_, Slot, i)->removeItem(1);
                                    sort();
                                }
                            }
                        }
                        // SLOT WAS RIGHT-CLICKED
                        else if (   component(wInve_, Slot, i)->isPressed(rw, e, sf::Mouse::Right)
                                && !component(wInve_, Slot, i)->isEmpty()
                                 ) {
                            wOpts.setPosition(component(wInve_, Slot, i)->getPosition()
                                             +component(wInve_, Slot, i)->getSize());

                            if (wOpts.getParentComponent() != component(wInve_, Slot, i)) {
                                wOpts.setParentComponent(component(wInve_, Slot, i));

                                Item* item = ((Slot*)wOpts.getParentComponent())->getItem();

                                if      (  instanceof<Equipable, Item>(item)
                                         ) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.equip"]);
                                else if (  instanceof<Potion   , Item>(item)
                                         ) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.drink"]);
                                else if (  instanceof<Food     , Item>(item)
                                         ) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.eat"]);
                                else if (  instanceof<Book     , Item>(item)
                                         ) component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.read"]);
                                else       component(wOpts, Menu, 0)->setOption(0, Resources::dictionary["gui.menu.use"]);

                                wOpts.setHeader(item->getName());
                                if (  wOpts.getHeader().getSize().x+10 >= 142
                                    ) wOpts.setSize(sf::Vector2f(wOpts.getHeader().getSize().x+10, 143));

                                else wOpts.setSize(sf::Vector2f(142, 143));
                                wOpts.setVisible(true);
                            }
                            else {
                                wOpts.setParentComponent(nullptr);
                                wOpts.setVisible(false);
                            }
                        }
                        else {
                            wInfo.setParentComponent(component(wInve_, Slot, i));
                            slotPointed = true;
                        }
                    }
                }
                /* CARRY-ON */
                for (int i=0; i<5; ++i) {
                    if (   sCarryOn_[i]->containsMouseCursor(rw)
                       && !sCarryOn_[i]->isEmpty()
                        ) {
                        if (   sCarryOn_[i]->isPressed(rw, e)
                           && !sCarryOn_[i]->isEmpty()
                            ) {
                            game->getPlayer()->useItem(sCarryOn_[i]->getItem());
                            if (sCarryOn_[i]->getItem()->isDisposable()) {
                                sCarryOn_[i]->removeItem(1);
                                sort();
                            }
                        }
                        else {
                            wInfo.setParentComponent(sCarryOn_[i]);
                            slotPointed = true;
                        }
                    }
                }

                // HANDLING THE ITEM INFO WINDOW
                if (!wOpts.isVisible() && slotPointed) {
                    component(wInfo, Text, 0)->setString(((Slot*)wInfo.getParentComponent())->getItem()->getDescription());
                    component(wInfo, Text, 0)->wrap     ((wInfo.getHeader().getSize().x>=300.f) ? wInfo.getHeader().getSize().x+10 : 300.f);

                    wInfo.setHeader  (((Slot*)wInfo.getParentComponent())->getItem()->getName());
                    wInfo.setSize    (component(wInfo, Text, 0)->getSize() + sf::Vector2f(10, 30));
                    wInfo.setPosition((sf::Vector2f) sf::Mouse::getPosition(rw) + sf::Vector2f(5, 5));

                    if (  wInfo.getPosition().x+wInfo.getSize().x+5 > (float)rw.getSize().x
                        ) wInfo.setPosition((sf::Vector2f) sf::Mouse::getPosition(rw)
                                            -sf::Vector2f(wInfo.getPosition().x + wInfo.getSize().x - (float)rw.getSize().x, -5));
                                            
                    if (  wInfo.getPosition().y+wInfo.getSize().y+5 > (float)rw.getSize().y
                        ) wInfo.setPosition((sf::Vector2f) sf::Mouse::getPosition(rw)
                                            -sf::Vector2f(-5, wInfo.getPosition().y + wInfo.getSize().y - (float)rw.getSize().y));

                    wInfo.setVisible(true);
                }
                else wInfo.setVisible(false);
            }
        }

#undef component
#undef wInfo
#undef wOpts

    }

    bool Inventory::addItem(Item* item) {
        if (  item == nullptr
            ) return false;

#define slot(i) wInve_.getComponent<Slot>(i)

     // in the beginning we check if the picked item is a coin
        if (instanceof<Coin, Item>(item)) {
         // first we recognize the coin type and size
            if (((Coin*)item)->getType() == Coin::BRONZE) {
                if (  ((Coin*)item)->getSize() == Coin::BIG
                    ) bronze_ += item->getAmount()*5;
                else  bronze_ += item->getAmount();
            }
            else if (((Coin*)item)->getType() == Coin::SILVER) {
                if (  ((Coin*)item)->getSize() == Coin::BIG
                    ) silver_ += item->getAmount()*5;
                else  silver_ += item->getAmount();
            }
            else if (((Coin*)item)->getType() == Coin::GOLDEN) {
                if (  ((Coin*)item)->getSize() == Coin::BIG
                    ) gold_ += item->getAmount()*5;
                else  gold_ += item->getAmount();
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
            for (int i=0; i<32; ++i) {
                if (!slot(i)->isEmpty() && slot(i)->getItem()->getID() == item->getID()) {
                    bool success = slot(i)->addItem(item);
                    sort();
                    return success;
                }
            }
        }

     // if not then we look for the first empty slot and add the item to it
        for (int i=0; i<32; ++i) {
            if (slot(i)->isEmpty()) {
                bool success = slot(i)->addItem(item);
                sort();
                return success;
            }
        }

     // and if there is no empty slot, we just exit the function
        return false;
    }

    void Inventory::sort() {
        for (int i=0; i<31; ++i) {
            for (int j=1; j<32; ++j) {
                if ( (!slot(j-1)->isEmpty() && slot(j)->isEmpty())
                   ||( slot(j-1)->isEmpty() && slot(j)->isEmpty())
                    ) continue;
                if ( (slot(j-1)->isEmpty() && !slot(j)->isEmpty())
                   ||(slot(j-1)->getItem()->getID() > slot(j)->getItem()->getID())
                    ) slot(j-1)->swapItems(slot(j));
            }
        }
    }

    bool Inventory::contains(Item* sought) {
        for (int i=0; i<32; ++i) {
	        if ( !slot(i)->isEmpty() && slot(i)->getItem()->getID() == sought->getID()
                ) return true;
        }
        return false;
    }

    void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (isOpen()) {
            target.draw(shadow_, states);
            target.draw(wInve_ , states);
        }
        for (auto slot : sCarryOn_) {
            target.draw(*slot  , states);
        }
    }

    void Inventory::open() {
        wInve_.getComponent<Text>(0)->setString(std::to_string((int) gold_));
        wInve_.getComponent<Text>(1)->setString(std::to_string((int) silver_));
        wInve_.getComponent<Text>(2)->setString(std::to_string((int) bronze_));

        wInve_.setVisible(true);
    }

    void Inventory::close() {
        wInve_.getComponent<Window>(1)->setVisible(false);
        wInve_.getComponent<Window>(1)->setParentComponent(nullptr);
        wInve_.setVisible(false);
    }

    std::ifstream& Inventory::operator<<(std::ifstream& file) {
        try {
            readFile <short> (file, bronze_);
            readFile <short> (file, silver_);
            readFile <short> (file, gold_);

            int itemsNumber;
            readFile <int> (file, itemsNumber);

            for (int i=0; i<itemsNumber; ++i) {
                int itemType;
                readFile <int> (file, itemType);
                
                Item* item = nullptr;
                switch (itemType) {
                    case 0: item = new Ammunition  (); readEntity(file, item); break;
                    case 1: item = new Book        (); readEntity(file, item); break;
                    case 2: item = new Coin        (); readEntity(file, item); break;
                    case 3: item = new ColdWeapon  (); readEntity(file, item); break;
                    case 4: item = new Food        (); readEntity(file, item); break;
                    case 5: item = new Potion      (); readEntity(file, item); break;
                    case 6: item = new RangedWeapon(); readEntity(file, item); break;
                    case 7: item = new Rune        (); readEntity(file, item); break;
                }
                addItem(item);
            }
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream& Inventory::operator>>(std::ofstream& file) {
        file << bronze_ << ' '
             << silver_ << ' '
             << gold_   << '\n';

        for (int i=0; i<32; ++i) {
            if (slot(i)->isEmpty()) {
                file << i << '\n';
                break;
            }
        }

        for (int i=0; i<32; ++i) {
            if (  slot(i)->isEmpty()
                ) break;
            *slot(i)->getItem() >> file << '\n';
        }

        return file;
    }

    void Inventory::onNotify(Event event, Entity* entity) {
        switch (event) {
            default: break;
        }

#undef slot

    }

}
