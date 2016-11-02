/**
 * @file src/program/game/entity/npc/NPCAttacking.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_STATE_ATTACKING_HPP
#define NPC_STATE_ATTACKING_HPP

#include "NPCState.hpp"

namespace rr
{

    class NPCAttacking : public NPCState
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Updates the state.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* update(sf::Time&, NPC*) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Reacts to an event.
                ////////////////////////////////////////////////////////////////////////
        virtual NPCState* react(Level*, NPC*, Player*) override;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Returns the string of the state.
                ////////////////////////////////////////////////////////////////////////
        virtual sf::String toString() const override;
    };

}

#endif // NPC_STATE_ATTACKING_HPP
