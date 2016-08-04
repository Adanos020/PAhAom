/**
 * @file src/program/game/messages/MessageManager.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "MessageManager.hpp"

#include "../Settings.hpp"
#include "../Resources.hpp"

#include "../game/entity/ALL.hpp"

namespace rr {

    void MessageManager::addMessage(Message message) {
        messages_.push_back(message);
        std::wcout << message.getString().toWideString() << '\n';

        float mHeight = messages_.back().getSize().y;
        messages_.back().setPosition(sf::Vector2f(0, Settings::graphics.resolution.y-40-mHeight));

        for (int i=messages_.size()-2; i>=0; i--) {
            mHeight = messages_[i].getSize().y;
            messages_[i].setPosition(messages_[i+1].getPosition() - sf::Vector2f(0, mHeight+3));
        }
    }

    void MessageManager::update(sf::Time timeStep) {
        for (auto i=messages_.begin(); i!=messages_.end(); ++i) {
            i->update(timeStep);
            if (i->getColor().a < 10) {
                messages_.erase(i);
                break;
            }
        }
    }

    void MessageManager::draw(sf::RenderWindow& rw) {
        for (auto message : messages_) {
            rw.draw(message);
        }
    }

    void MessageManager::onNotify(Event event, Entity* entity) {
        switch (event) {
            case ITEM_EQUIP_FAILURE: addMessage(Message(Resources::dictionary["message.item_equip_failure"]
                                                      +" "
                                                      +((Item*)entity)->getName()
                                                      +((Settings::game.language != "fc") ? sf::String("!") : sf::String("")), sf::Color::Red));
                                     break;

            case ITEM_DISCOVERED   : addMessage(Message(Resources::dictionary["message.item_discovered"]+" "
                                                      +((Item*)entity)->getName()
                                                      +((Settings::game.language != "fc") ? sf::String(".") : sf::String("")), sf::Color::Yellow));
                                     break;

            case ITEM_PICKED       : addMessage(Message(Resources::dictionary["message.item_picked"]
                                                       +sf::String(" ")
                                                       +std::to_string((instanceof<Coin, Item>((Item*)entity) && ((Coin*)entity)->size_ == Coin::BIG) ? 5*((Item*)entity)->getAmount() : ((Item*)entity)->getAmount())
                                                       +sf::String("x ")
                                                       +((Item*)entity)->getName()
                                                       +((Settings::game.language != "fc") ? sf::String("!") : sf::String(""))));
                                     break;

            case ITEM_USED         : if (instanceof<Book, Item>((Item*)entity)) {
                                         switch (((Book*)entity)->type_) {
                                             case Book  ::CRAFTING             : addMessage(Message(Resources::dictionary["message.item_used.book.crafting"             ])); break;
                                             case Book  ::ALCHEMY              : addMessage(Message(Resources::dictionary["message.item_used.book.alchemy"              ])); break;
                                             case Book  ::COLD_WEAPON_MASTERY  : addMessage(Message(Resources::dictionary["message.item_used.book.cold_weapon_mastery"  ])); break;
                                             case Book  ::RANGED_WEAPON_MASTERY: addMessage(Message(Resources::dictionary["message.item_used.book.ranged_weapon_mastery"])); break;
                                             case Book  ::EAGLE_EYE            : addMessage(Message(Resources::dictionary["message.item_used.book.eagle_eye"            ])); break;
                                             case Book  ::MANA_REGEN           : addMessage(Message(Resources::dictionary["message.item_used.book.mana_regen"           ])); break;
                                             case Book  ::HEALTH_REGEN         : addMessage(Message(Resources::dictionary["message.item_used.book.health_regen"         ])); break;
                                             case Book  ::FASTER_LEARNING      : addMessage(Message(Resources::dictionary["message.item_used.book.faster_learning"      ])); break;
                                             default: break;
                                         }
                                     }
                                     else if (instanceof<Food, Item>((Item*)entity)) {
                                         addMessage(Message(Resources::dictionary["message.item_used.food"]));
                                     }
                                     else if (instanceof<Potion, Entity>((Item*)entity)) {
                                         switch (((Potion*)entity)->effect_) {
                                             case Potion::HEALING              : addMessage(Message(Resources::dictionary["message.item_used.potion.healing"            ])); break;
                                             case Potion::MAGIC                : addMessage(Message(Resources::dictionary["message.item_used.potion.magic"              ])); break;
                                             case Potion::STRENGTH             : addMessage(Message(Resources::dictionary["message.item_used.potion.strength"           ])); break;
                                             case Potion::DEXTERITY            : addMessage(Message(Resources::dictionary["message.item_used.potion.dexterity"          ])); break;
                                             case Potion::SPEED                : addMessage(Message(Resources::dictionary["message.item_used.potion.speed"              ])); break;
                                             case Potion::REGENERATION         : addMessage(Message(Resources::dictionary["message.item_used.potion.regeneration"       ])); break;
                                             case Potion::POISON               : addMessage(Message(Resources::dictionary["message.item_used.potion.poison"             ])); break;
                                             case Potion::SLOWNESS             : addMessage(Message(Resources::dictionary["message.item_used.potion.slowness"           ])); break;
                                             case Potion::WEAKNESS             : addMessage(Message(Resources::dictionary["message.item_used.potion.weakness"           ])); break;
                                         }
                                     }
                                     else if (instanceof<Rune, Item>((Item*)entity)) {
                                     
                                     }
                                     break;

            default                : break;
        }
    }

}
