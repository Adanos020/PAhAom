/**
 * @file src/program/game/entities/item/Item.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>

#include "../../../Resources.hpp"

#include "../Entity.hpp"

namespace rr
{

/// Class for an item
    class Item : public Entity
    {
    protected: sf::VertexArray body_;
               bool            disposable_;
               bool            stackable_;
               bool            cursed_;
               int             ID_;
               int             amount_;
               unsigned        iconIndex_;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Draws the item's body and texture on the screen.
               ////////////////////////////////////////////////////////////////////////
       virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
               {
                   states.texture = &Resources::texture.items;
                   target.draw(body_, states);
               }

    public:    ////////////////////////////////////////////////////////////////////////
               /// \brief Virtual destructor.
               ////////////////////////////////////////////////////////////////////////
       virtual ~Item() {}

               ////////////////////////////////////////////////////////////////////////
               /// \brief Changes the amount
               ////////////////////////////////////////////////////////////////////////
       virtual void setAmount(int x) { amount_ = x; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the item's ID
               ////////////////////////////////////////////////////////////////////////
       virtual int getID() const { return ID_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the amount of this item
               ////////////////////////////////////////////////////////////////////////
       virtual int getAmount() const { return amount_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the item is disposable
               ////////////////////////////////////////////////////////////////////////
       virtual bool isDisposable() const { return disposable_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the item is stackable
               ////////////////////////////////////////////////////////////////////////
       virtual bool isStackable() const { return stackable_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the item is cursed
               ////////////////////////////////////////////////////////////////////////
       virtual bool isCursed() const { return cursed_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the sprite of this item
               ////////////////////////////////////////////////////////////////////////
       virtual sf::VertexArray getBody() const { return body_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the name of this item
               ////////////////////////////////////////////////////////////////////////
       virtual sf::String getName() const = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the description of this item
               ////////////////////////////////////////////////////////////////////////
       virtual sf::String getDescription() const = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the texture's icon index
               ////////////////////////////////////////////////////////////////////////
       virtual unsigned getIconIndex() const { return iconIndex_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the item's position relatively to the grid marked out by
               /// the level's tile map.
               ////////////////////////////////////////////////////////////////////////
       virtual void setGridPosition(sf::Vector2i pos) override
               {
                   body_[0].position = (sf::Vector2f)pos*80.f;
                   body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f);
                   body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
                   body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);
               }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the item's position relatively to the grid marked out
               /// by the level's tile map.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::Vector2i getGridPosition() const override { return (sf::Vector2i) body_[0].position/80; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Sets the item's position relatively to the graphics card's
               /// coordinate system.
               ////////////////////////////////////////////////////////////////////////
       virtual void setPosition(sf::Vector2f pos) override
               {
                   body_[0].position =               pos;
                   body_[1].position =  sf::Vector2f(pos.x+80, pos.y);
                   body_[2].position =  sf::Vector2f(pos.x+80, pos.y+80);
                   body_[3].position =  sf::Vector2f(pos.x   , pos.y+80);
               }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the item's position relatively to the graphics card's
               /// coordinate system.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::Vector2f getPosition() const override { return body_[0].position/80.f; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if another entity's bound box intersects with the item's
               /// bound box.
               ////////////////////////////////////////////////////////////////////////
       virtual bool collides(Entity* e) const override { return (e->getBounds().intersects(getBounds())); }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the item's bound box.
               ////////////////////////////////////////////////////////////////////////
       virtual sf::FloatRect getBounds() const override { return sf::FloatRect(body_[0].position, body_[2].position-body_[0].position); }
    };

    class Discoverable : public Item
    {
    public: ////////////////////////////////////////////////////////////////////////
            /// \brief Virtual destructor.
            ////////////////////////////////////////////////////////////////////////
    virtual ~Discoverable() {}

            ////////////////////////////////////////////////////////////////////////
            /// \brief Reveals the item's properties.
            ////////////////////////////////////////////////////////////////////////
    virtual void reveal() = 0;

            ////////////////////////////////////////////////////////////////////////
            /// \brief Tells if the item is discovered.
            ////////////////////////////////////////////////////////////////////////
    virtual bool isDiscovered() const = 0;
    };

    class Equipable : public Discoverable
    {
    protected: bool equipped_ = false;
    
    public:    ////////////////////////////////////////////////////////////////////////
               /// \brief Virtual destructor.
               ////////////////////////////////////////////////////////////////////////
       virtual ~Equipable() {}

               ////////////////////////////////////////////////////////////////////////
               /// Equips or unequips the item.
               ////////////////////////////////////////////////////////////////////////
       virtual void equip(bool) = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the item is equipped.
               ////////////////////////////////////////////////////////////////////////
       virtual bool isEquipped() const = 0;
    };

    class Weapon : public Equipable
    {
    protected: float requirement_;
               float damageDealt_;
               float speed_;
               float accuracy_;
               int   level_;
               bool  identified_;

    public:    ////////////////////////////////////////////////////////////////////////
               /// \brief Virtual destructor.
               ////////////////////////////////////////////////////////////////////////
       virtual ~Weapon() {}

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the weapon's requirement.
               ////////////////////////////////////////////////////////////////////////
               float getRequirement() const { return requirement_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the weapon's maximum damage dealt.
               ////////////////////////////////////////////////////////////////////////
               float getDamageDealt() const { return damageDealt_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the weapon's speed.
               ////////////////////////////////////////////////////////////////////////
               float getSpeed() const { return speed_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the weapon's accuracy.
               ////////////////////////////////////////////////////////////////////////
               float getAccuracy() const { return accuracy_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Returns the weapon's upgrade level.
               ////////////////////////////////////////////////////////////////////////
               int getLevel() const { return level_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells everything about the weapon.
               ///
               /// This allows the player to see the actual level and enchantments of
               /// the weapon.
               ////////////////////////////////////////////////////////////////////////
       virtual void reveal() override { identified_ = true; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the weapon is discovered.
               ////////////////////////////////////////////////////////////////////////
       virtual bool isDiscovered() const override { return identified_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Makes the weapon equipped.
               ////////////////////////////////////////////////////////////////////////
       virtual void equip(bool b) override { equipped_ = b; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Tells if the weapon is equipped.
               ////////////////////////////////////////////////////////////////////////
       virtual bool isEquipped() const override { return equipped_; }

               ////////////////////////////////////////////////////////////////////////
               /// \brief Increases the weapon's level and maximum damage dealt by
               /// it and reduces its requirement.
               ////////////////////////////////////////////////////////////////////////
       virtual void enhance() = 0;

               ////////////////////////////////////////////////////////////////////////
               /// \brief Puts an enchantment on the cold weapon.
               ////////////////////////////////////////////////////////////////////////
       virtual void enchant() = 0;
    };

}

#endif // ITEM_HPP
