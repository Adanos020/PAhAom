/**
 * @file src/program/game/entity/Chest.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef ENTITY_CHEST_HPP
#define ENTITY_CHEST_HPP

#include "../../funcs/items.hpp"

#include "Entity.hpp"
#include "item/Item.hpp"

namespace rr
{

    class Item;

    class Chest : public Entity
    {
    private: sf::Sprite m_body;
             Item*      m_item;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the chest.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the chest's body and texture on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    public:  enum Type
             {
                 REGULAR,
                 SPECIAL
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Chest(Type = REGULAR);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Chest(Chest const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
            ~Chest();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the chest's type.
             ///
             /// The possible values are:
             /// - REGULAR (contains regular loot like a potion, low/medium tier
             /// weapon, food, money, etc.)
             /// - SPECIAL (contains a rare or special item)
             ////////////////////////////////////////////////////////////////////////
             Type getType() const { return m_type; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the chest.
             ////////////////////////////////////////////////////////////////////////
     virtual Entity* clone() const override { return new Chest(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the chest's position relatively to the grid marked out
             /// by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual void setGridPosition(sf::Vector2i pos) override { m_body.setPosition((sf::Vector2f)pos*80.f); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the chest's position relatively to the grid marked
             /// out by the level's tile map.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2i getGridPosition() const override { return (sf::Vector2i) m_body.getPosition()/80; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sets the chest's position relatively to the graphics card's
             /// coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual void setPosition(sf::Vector2f pos) override { m_body.setPosition(pos); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the chest's position relatively to the graphics
             /// card's coordinate system.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::Vector2f getPosition() const override { return m_body.getPosition(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if another entity's bound box intersects with the
             /// chest's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual bool collides(Entity* e) const override { return e->getBounds().intersects(getBounds()); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the chest's bound box.
             ////////////////////////////////////////////////////////////////////////
     virtual sf::FloatRect getBounds() const override { return m_body.getGlobalBounds(); }

             ////////////////////////////////////////////////////////////////////////
             /// Returns the item which the chest contains
             ////////////////////////////////////////////////////////////////////////
             Item* getItem() const { return m_item; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the chest from the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the chest to the file.
             ////////////////////////////////////////////////////////////////////////
     virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type m_type;
    };

}

#endif // ENTITY_CHEST_HPP
