/**
 * @file src/program/game/entities/item/item.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_h
#define item_h

#include <SFML/Graphics.hpp>

#include "../entities.hpp"

namespace rr {

/// Class for an item
    class Item : public Entity {
    protected:
        sf::VertexArray body_;
        sf::String      name_;
        sf::String      description_;
        bool            equipable_;
        bool            disposable_;
        bool            stackable_;
        int             ID_;
        int             amount_;
        unsigned        iconIndex_;
    public:
    /// A virtual destructor
        virtual ~Item() {}

    /// Changes the amount
        virtual void               setAmount      (int x)                     { amount_ = x; }

    /// Returns the item's ID
        virtual int                getID          () const                    { return ID_; }

    /// Returns the amount of this item
        virtual int                getAmount      () const                    { return amount_; }

    /// Tells if the item is disposable
        virtual bool               isDisposable   () const                    { return disposable_; }

    /// Tells if the item is stackable
        virtual bool               isStackable    () const                    { return stackable_; }

    /// Tells if the item is equipable
        virtual bool               isEquipable    () const                    { return equipable_; }

    /// Returns the sprite of this item
        virtual sf::VertexArray    getBody        () const                    { return body_; }

    /// Returns the name of this item
        virtual sf::String         getName        () const                    { return name_; }

    /// Returns the description of this item
        virtual sf::String         getDescription () const                    { return description_; }

    /// Returns the texture's icon index
        virtual unsigned           getIconIndex   () const                    { return iconIndex_; }


        virtual void       setRealPosition(sf::Vector2f pos) override { body_[0].position = (sf::Vector2f)pos;
                                                                        body_[1].position =  sf::Vector2f(pos.x+80, pos.y);
                                                                        body_[2].position =  sf::Vector2f(pos.x+80, pos.y+80);
                                                                        body_[3].position =  sf::Vector2f(pos.x   , pos.y+80);
                                                                      }
        virtual void       setPosition    (sf::Vector2i pos) override { body_[0].position = (sf::Vector2f)pos*80.f;
                                                                        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
                                                                        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
                                                                        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);
                                                                      }
        virtual bool          intersects     (Entity* e) const override { return (e->getBounds().intersects(getBounds())); }
        virtual sf::FloatRect getBounds      ()          const override { return sf::FloatRect(body_[0].position, body_[2].position-body_[0].position); }
        virtual sf::Vector2i  getPosition    ()          const override { return (sf::Vector2i)body_[0].position/80; }
        virtual sf::Vector2f  getRealPosition()          const override { return body_[0].position; }
    };

    class Discoverable {
    protected:
        bool discovered_ = false;
        sf::String discoveredName_;
        sf::String discoveredDescription_;
    public:
    /// A virtual destructor
        virtual ~Discoverable() {}

    /// Method reveling the discoverable item's properties
        virtual void reveal      () = 0;
        bool         isDiscovered() { return discovered_; }
    };

}

#include "item_Book.hpp"
#include "item_Coin.hpp"
#include "item_ColdWeapon.hpp"
#include "item_Food.hpp"
#include "item_Potion.hpp"
#include "item_RangedWeapon.hpp"
#include "item_Spell.hpp"

#endif
