/**
 * @file src/program/game/ui/Inventory.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "../../Observer.hpp"

#include "../../gui/Window.hpp"
#include "../../gui/Slot.hpp"

#include "../Entity.hpp"

namespace rr
{

    class Game;
    class Player;

    class Inventory : public Observer, public sf::Drawable
    {
    private: sf::RectangleShape m_shadow;

             Window             m_wInve;
             Slot*              m_sCarryOn[5];
             Player*            m_player;

             short              m_bronze;
             short              m_silver;
             short              m_gold;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Sorts the items in the backpack.
             ////////////////////////////////////////////////////////////////////////
             void sort();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the window on the screen.
             ////////////////////////////////////////////////////////////////////////
     virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reacts to a specific event. It can either do something with
             /// a given entity or just ignore it.
             ////////////////////////////////////////////////////////////////////////
     virtual void onNotify(Event, Entity*, sf::String) override;

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Inventory(Player*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
             ~Inventory();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the interface.
             ////////////////////////////////////////////////////////////////////////
             void reset();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Adds an item to the inventory.
             ////////////////////////////////////////////////////////////////////////
             bool addItem(Item*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Removes an item from the inventory.
             ///
             /// If the amount is equal to 0 then all units of the item will be
             /// removed.
             ////////////////////////////////////////////////////////////////////////
             void removeItem(Item*, int amount = 0);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if there is such an item in the inventory.
             ////////////////////////////////////////////////////////////////////////
             bool contains(Item*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells how much gold there is in the inventory.
             ////////////////////////////////////////////////////////////////////////
             short getGold() const { return m_gold; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells how much silver there is in the inventory.
             ////////////////////////////////////////////////////////////////////////
             short getSilver() const { return m_silver; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells how much bronze there is in the inventory.
             ////////////////////////////////////////////////////////////////////////
             short getBronze() const { return m_bronze; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Clears the inventory.
             ////////////////////////////////////////////////////////////////////////
             void clear();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&, Game*);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Opens the inventory window.
             ////////////////////////////////////////////////////////////////////////
             void open();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Closes the inventory window.
             ////////////////////////////////////////////////////////////////////////
             void close();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the inventory is open.
             ////////////////////////////////////////////////////////////////////////
             bool isOpen() const { return m_wInve.isVisible(); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the inventory from a file.
             ////////////////////////////////////////////////////////////////////////
             std::ifstream& operator<<(std::ifstream&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the inventory to a file.
             ////////////////////////////////////////////////////////////////////////
             std::ofstream& operator>>(std::ofstream&);
    };

}

#include "../../Game.hpp"
#include "../entity/Player.hpp"
