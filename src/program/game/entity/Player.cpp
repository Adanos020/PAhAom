/**
 * @file src/program/game/entity/Player.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Player.hpp"
#include "item/ALL.hpp"

#include "../../Resources.hpp"
#include "../../observer/Observer.hpp"

#include "../../funcs/files.hpp"
#include "../../funcs/classes.hpp"

extern rr::Subject   subject;

namespace rr {

    Player::Player() :
      position_                    (sf::Vector2i(0, 0)),
      currentAnimation_            (&walkingRight_    ),
      moving_                      (false             ),
      velocity_                    (1120.f            ),
      sightRange_                  (5                 )
    {
        attrs_.health = attrs_.maxHealth =  30.f;
        attrs_.mana   = attrs_.maxMana   =   5.f;
        attrs_.strength                  =  10.f;
        attrs_.dexterity                 =  10.f;
        attrs_.experience                =   0.f;
        attrs_.nextLevel                 = 100.f;
        attrs_.level                     =   0  ;
        attrs_.skillPoints               =   0.f;
        attrs_.armor                     =   0.f;

        attrs_.crafting                  = false;
        attrs_.alchemy                   = false;
        attrs_.cold_weapon_mastery       = false;
        attrs_.ranged_weapon_mastery     = false;
        attrs_.eagle_eye                 = false;
        attrs_.mana_regeneration         = false;
        attrs_.health_regeneration       = false;
        attrs_.faster_learning           = false;

        buffs_.speed                     = 0;
        buffs_.regeneration              = 0;
        buffs_.poison                    = 0;
        buffs_.slowness                  = 0;
        buffs_.weakness                  = 0;
        buffs_.hunger                    = 0;

        initialize();
        body_.setPosition(sf::Vector2f(0, 0));
        body_.scale      (sf::Vector2f(5, 5));
    }

    Player::Player(Player const& player) :
      attrs_                       (player.attrs_           ),
      position_                    (player.position_        ),
      body_                        (player.body_            ),
      walkingLeft_                 (player.walkingLeft_     ),
      walkingRight_                (player.walkingRight_    ),
      currentAnimation_            (player.currentAnimation_),
      moving_                      (player.moving_          ),
      velocity_                    (player.velocity_        ),
      sightRange_                  (player.sightRange_      ) {}

    void Player::initialize() {
        walkingLeft_ .setSpriteSheet(Resources::texture.player );
        walkingRight_.setSpriteSheet(Resources::texture.player );
        walkingLeft_ .addFrame      (sf::IntRect(0, 16, 16, 16));
        walkingRight_.addFrame      (sf::IntRect(0, 0,  16, 16));

        body_        .setLooped     (false);
        body_        .pause         ();
    }

    void Player::move(int tiles[], Direction di) {
        if (!moving_) {
            if (di == UP    && (tiles[position_.x   + (position_.y-1)*77] != 1 && tiles[position_.x   + (position_.y-1)*77] != 5)) {
                position_ = sf::Vector2i(position_.x, position_.y-1);
                moving_ = true;
            }
            if (di == DOWN  && (tiles[position_.x   + (position_.y+1)*77] != 1 && tiles[position_.x   + (position_.y+1)*77] != 5)) {
                position_ = sf::Vector2i(position_.x, position_.y+1);
                moving_ = true;
            }
            if (di == LEFT) {
                if (tiles[position_.x-1 + position_.y*77] != 1 && tiles[position_.x-1 + position_.y*77] != 5) {
                    position_ = sf::Vector2i(position_.x-1, position_.y);
                    moving_ = true;
                }
                currentAnimation_ = &walkingLeft_;
            }
            if (di == RIGHT) {
                if (tiles[position_.x+1 + position_.y*77] != 1 && tiles[position_.x+1 + position_.y*77] != 5) {
                    position_ = sf::Vector2i(position_.x+1, position_.y);
                    moving_ = true;
                }
                currentAnimation_ = &walkingRight_;
            }
        }
    }

    void Player::update(sf::Time timeStep) {
        if (moving_) {
            sf::Vector2f offset = body_.getPosition()-(sf::Vector2f)position_*80.f;
            if (offset != sf::Vector2f(0, 0)) {
                if (offset.x < 0) body_.move(sf::Vector2f( velocity_*timeStep.asSeconds(),  0));
                if (offset.x > 0) body_.move(sf::Vector2f(-velocity_*timeStep.asSeconds(),  0));
                if (offset.y < 0) body_.move(sf::Vector2f( 0,  velocity_*timeStep.asSeconds()));
                if (offset.y > 0) body_.move(sf::Vector2f( 0, -velocity_*timeStep.asSeconds()));
            }
            else {
                buffs_.speed        -= (buffs_.speed        == 0 ? 0 : 1);
                buffs_.regeneration -= (buffs_.regeneration == 0 ? 0 : 1);
                buffs_.poison       -= (buffs_.poison       == 0 ? 0 : 1);
                buffs_.slowness     -= (buffs_.slowness     == 0 ? 0 : 1);
                buffs_.weakness     -= (buffs_.weakness     == 0 ? 0 : 1);
                buffs_.hunger       ++;
                moving_ = false;
            }

            if (  (abs(offset.x) < velocity_/256 && abs(offset.x) > 0) // preventing the player from wobbling
               || (abs(offset.y) < velocity_/256 && abs(offset.y) > 0) // in between of two cells
                )  body_.setPosition((sf::Vector2f)position_*80.f);
        }

        if (attrs_.health     >= attrs_.maxHealth) attrs_.health       = attrs_.maxHealth;
        if (attrs_.health     <= 0)                attrs_.health       = 0;
        if (attrs_.mana       <= 0)                attrs_.mana         = 0;
        if (attrs_.mana       >= attrs_.maxMana)   attrs_.mana         = attrs_.maxMana;
        if (attrs_.experience >= attrs_.nextLevel) {
                                                   attrs_.experience   = 0;
                                                   attrs_.nextLevel   *= 1.25f;
                                                   attrs_.level       ++;
                                                   attrs_.skillPoints += (attrs_.faster_learning) ? 15 : 10;

                                                   float temp          = attrs_.health/attrs_.maxHealth;
                                                   attrs_.maxHealth   += 10;
                                                   attrs_.health       = temp*attrs_.maxHealth;

                                                   temp                = attrs_.mana/attrs_.maxMana;
                                                   attrs_.maxMana     += 1;
                                                   attrs_.mana         = temp*attrs_.maxMana;
        }

        body_.update(timeStep);
        body_.play  (*currentAnimation_);
    }

    void Player::attack(NPC* npc) {
        int maxDamage = attrs_.strength;
        if (  coldWeapon_ != nullptr
            ) maxDamage = coldWeapon_->getDamageDealt() - (coldWeapon_->getStrengthRequired() - attrs_.strength);

        npc->handleDamage(rand()%maxDamage);
    }

    void Player::handleDamage(int damage) {
        if (  damage >= attrs_.armor
            ) attrs_.health -= (damage - attrs_.armor);
    }

    void Player::reset() {
        attrs_.health                =  30.f;
        attrs_.mana                  =   5.f;
        attrs_.maxHealth             =  30.f;
        attrs_.maxMana               =   5.f;
        attrs_.strength              =  10.f;
        attrs_.dexterity             =  10.f;
        attrs_.experience            =   0.f;
        attrs_.nextLevel             = 100.f;
        attrs_.level                 =   0  ;
        attrs_.skillPoints           =   0.f;
        attrs_.armor                 =   0.f;

        attrs_.crafting              = false;
        attrs_.alchemy               = false;
        attrs_.cold_weapon_mastery   = false;
        attrs_.ranged_weapon_mastery = false;
        attrs_.eagle_eye             = false;
        attrs_.mana_regeneration     = false;
        attrs_.health_regeneration   = false;
        attrs_.faster_learning       = false;
    }

    void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &Resources::texture.player;
        target.draw(body_, states);
    }

    void Player::useItem(Item* item) {
        if (instanceof<Discoverable, Item>(item) && !((Discoverable*)item)->isDiscovered()) {
            ((Discoverable*)item)->reveal();
            subject.notify(Observer::ITEM_DISCOVERED, item);
        }

        subject.notify(Observer::ITEM_USED, item);

        if (instanceof<Book, Item>(item)) {
            switch (((Book*)item)->type_) {
                case Book::CRAFTING             : attrs_.crafting              = true; break;
                case Book::ALCHEMY              : attrs_.alchemy               = true; break;
                case Book::COLD_WEAPON_MASTERY  : attrs_.cold_weapon_mastery   = true; break;
                case Book::RANGED_WEAPON_MASTERY: attrs_.ranged_weapon_mastery = true; break;
                case Book::EAGLE_EYE            : attrs_.eagle_eye             = true; break;
                case Book::MANA_REGEN           : attrs_.mana_regeneration     = true; break;
                case Book::HEALTH_REGEN         : attrs_.health_regeneration   = true; break;
                case Book::FASTER_LEARNING      : attrs_.faster_learning       = true; break;
                default                         :                                      break;
            }
        }
        else if (instanceof<Food, Item>(item)) {
            if (  buffs_.hunger >= 200
                ) buffs_.hunger  = 100;
            else  buffs_.hunger  =   0;
        }
        else if (instanceof<Potion, Item>(item)) {
            switch (((Potion*)item)->effect_) {
                case Potion::HEALING     : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : attrs_.health       += attrs_.maxHealth*0.25; break;
                                               case Potion::MEDIUM: attrs_.health       += attrs_.maxHealth*0.50; break;
                                               case Potion::BIG   : attrs_.health       += attrs_.maxHealth*0.75; break;
                                           } break;

                case Potion::MAGIC       : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : attrs_.mana         += attrs_.maxMana * 0.25; break;
                                               case Potion::MEDIUM: attrs_.mana         += attrs_.maxMana * 0.50; break;
                                               case Potion::BIG   : attrs_.mana         += attrs_.maxMana * 0.75; break;
                                           } break;

                case Potion::STRENGTH    : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : attrs_.strength     += 1                    ; break;
                                               case Potion::MEDIUM: attrs_.strength     += 3                    ; break;
                                               case Potion::BIG   : attrs_.strength     += 5                    ; break;
                                           } break;

                case Potion::DEXTERITY   : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : attrs_.dexterity    += 1                    ; break;
                                               case Potion::MEDIUM: attrs_.dexterity    += 3                    ; break;
                                               case Potion::BIG   : attrs_.dexterity    += 5                    ; break;
                                           } break;

                case Potion::SPEED       : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : buffs_.speed        += 10                   ; break;
                                               case Potion::MEDIUM: buffs_.speed        += 30                   ; break;
                                               case Potion::BIG   : buffs_.speed        += 50                   ; break;
                                           } break;

                case Potion::REGENERATION: switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : buffs_.regeneration += 10                   ; break;
                                               case Potion::MEDIUM: buffs_.regeneration += 30                   ; break;
                                               case Potion::BIG   : buffs_.regeneration += 50                   ; break;
                                           } break;

                case Potion::POISON      : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : buffs_.poison       += 10                   ; break;
                                               case Potion::MEDIUM: buffs_.poison       += 30                   ; break;
                                               case Potion::BIG   : buffs_.poison       += 50                   ; break;
                                           } break;

                case Potion::SLOWNESS    : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : buffs_.slowness     += 10                   ; break;
                                               case Potion::MEDIUM: buffs_.slowness     += 30                   ; break;
                                               case Potion::BIG   : buffs_.slowness     += 50                   ; break;
                                           } break;

                case Potion::WEAKNESS    : switch (((Potion*)item)->size_) {
                                               case Potion::SMALL : buffs_.weakness     += 10                   ; break;
                                               case Potion::MEDIUM: buffs_.weakness     += 30                   ; break;
                                               case Potion::BIG   : buffs_.weakness     += 50                   ; break;
                                           } break;
            }
        }
        else if (instanceof<Rune, Item>(item)) {

        }
    }

    bool Player::equipItem(Equipable* item, bool equip) {
        bool success = false;
        if (instanceof <ColdWeapon, Equipable> (item)) {
            if (!equip) {
                coldWeapon_ = nullptr;
                success     = true;
            }
            else if (((ColdWeapon*)item)->getStrengthRequired() <= attrs_.strength) {
                coldWeapon_ = (ColdWeapon*)item;
                success     = true;
            }
        }

        if (success) {
            if (!item->isDiscovered()) {
                item->reveal();
                subject.notify(Observer::ITEM_DISCOVERED, item);
            }
        }
        else subject.notify(Observer::ITEM_EQUIP_FAILURE, item);

        return success;
    }

    std::ifstream& Player::operator<<(std::ifstream& file) {
        currentAnimation_->clearFrames();
        
        try {
            readFile <float> (file, attrs_.health);
            readFile <float> (file, attrs_.mana);
            readFile <float> (file, attrs_.maxHealth);
            readFile <float> (file, attrs_.maxMana);
            readFile <float> (file, attrs_.strength);
            readFile <float> (file, attrs_.dexterity);
            readFile <float> (file, attrs_.experience);
            readFile <float> (file, attrs_.nextLevel);
            readFile < int > (file, attrs_.level);
            readFile <float> (file, attrs_.skillPoints);
                
            readFile < bool> (file, attrs_.crafting);
            readFile < bool> (file, attrs_.alchemy);
            readFile < bool> (file, attrs_.cold_weapon_mastery);
            readFile < bool> (file, attrs_.ranged_weapon_mastery);
            readFile < bool> (file, attrs_.eagle_eye);
            readFile < bool> (file, attrs_.mana_regeneration);
            readFile < bool> (file, attrs_.health_regeneration);
            readFile < bool> (file, attrs_.faster_learning);
                
            readFile < int > (file, position_.x);
            readFile < int > (file, position_.y);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        initialize();
        setGridPosition(position_);
        
        return file;
    }

    std::ofstream& Player::operator>>(std::ofstream& file) {
        file << attrs_.health                << ' '
             << attrs_.mana                  << ' '
             << attrs_.maxHealth             << ' '
             << attrs_.maxMana               << ' '
             << attrs_.strength              << ' '
             << attrs_.dexterity             << ' '
             << attrs_.experience            << ' '
             << attrs_.nextLevel             << ' '
             << attrs_.level                 << ' '
             << attrs_.skillPoints           << ' '
             
             << attrs_.crafting              << ' '
             << attrs_.alchemy               << ' '
             << attrs_.cold_weapon_mastery   << ' '
             << attrs_.ranged_weapon_mastery << ' '
             << attrs_.eagle_eye             << ' '
             << attrs_.mana_regeneration     << ' '
             << attrs_.health_regeneration   << ' '
             << attrs_.faster_learning       << ' '
             
             << position_.x                  << ' '
             << position_.y;
        
        return file;
    }

}
