/**
 * @file src/program/Game.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#pragma once

#include <vector>

#include "game/Level.hpp"
#include "game/ui/ALL.hpp"
#include "game/entity/ALL.hpp"

#include "game/MessageManager.hpp"
#include "game/HitMarkerManager.hpp"
#include "AudioManager.hpp"

namespace rr
{

    class MainMenu;
    class PauseMenu;
    class Attributes;
    class Inventory;
    class Journal;
    class BookOfSpells;
    class HUD;

    class Level;
    class FOV;
    class MessageManager;
    class HitMarkerManager;

    class Player;

    class Bar;
    class Slot;
    class Text;

    class Game
    {
    private: sf::View         m_gameView;
             sf::View         m_mapView;

             Level*           m_currentLevel;

             AudioManager     m_audioManager;
             MessageManager   m_messageManager;
             HitMarkerManager m_hitMarkerManager;

             Player           m_player;

             Attributes       m_attributes;
             BookOfSpells     m_bookOfSpells;
             Conversation     m_conversation;
             DeathScreen      m_deathScreen;
             Inventory        m_inventory;
             Journal          m_journal;
             HUD              m_hud;
             MainMenu         m_mainMenu;
             PauseMenu        m_pauseMenu;

             bool             m_started;
             bool             m_paused;
             bool             m_mapOpen;

             bool             m_lost;

             unsigned         m_levelNumber;
             unsigned         m_seed;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Keyboard controls.
             ////////////////////////////////////////////////////////////////////////
             void controls(sf::Event&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Randomizes the disposable items' colors/symbols.
             ////////////////////////////////////////////////////////////////////////
             void randomizeItems();

    public:  ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Game();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Destructor.
             ////////////////////////////////////////////////////////////////////////
            ~Game();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Draws the game components.
             ////////////////////////////////////////////////////////////////////////
             void draw(sf::RenderWindow&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Handles the button events.
             ////////////////////////////////////////////////////////////////////////
             void buttonEvents(sf::RenderWindow&, sf::Event&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Updates the game's state.
             ////////////////////////////////////////////////////////////////////////
             void update(sf::Event&, sf::Time&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Switches to the level of a given index.
             ////////////////////////////////////////////////////////////////////////
             void switchLevel(int index);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the user interface after applying changes to the
             /// window settings.
             ////////////////////////////////////////////////////////////////////////
             void resetUI();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Starts the game or not, depending on the argument's value.
             ////////////////////////////////////////////////////////////////////////
             void start(bool);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Pauses the game or not, depending on the argument's value.
             ////////////////////////////////////////////////////////////////////////
             void pause(bool);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the game progress.
             ////////////////////////////////////////////////////////////////////////
             void save();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Loads the game progress.
             ////////////////////////////////////////////////////////////////////////
             bool load();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Starts the new game.
             ////////////////////////////////////////////////////////////////////////
             bool loadNewGame();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Called after the player loses the game.
             ////////////////////////////////////////////////////////////////////////
             void lose();

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the game is started.
             ////////////////////////////////////////////////////////////////////////
             bool isStarted() { return m_started; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the game is paused.
             ////////////////////////////////////////////////////////////////////////
             bool isPaused() { return m_paused; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Tells if the game is lost.
             ////////////////////////////////////////////////////////////////////////
             bool isLost() { return m_lost; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the pointer to the player.
             ////////////////////////////////////////////////////////////////////////
             Player* getPlayer() { return &m_player; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the inventory.
             ////////////////////////////////////////////////////////////////////////
             Inventory* getInventory() { return &m_inventory; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the conversation UI.
             ////////////////////////////////////////////////////////////////////////
             Conversation* getConversationUI() { return &m_conversation; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the vector of game levels.
             ////////////////////////////////////////////////////////////////////////
             Level* getCurrentLevel() { return m_currentLevel; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the audio manager.
             ////////////////////////////////////////////////////////////////////////
             AudioManager* getAudioManager() { return &m_audioManager; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the message manager.
             ////////////////////////////////////////////////////////////////////////
             MessageManager* getMessageManager() { return &m_messageManager; }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Resets the game state.
             ////////////////////////////////////////////////////////////////////////
             void reset();
    };

}
