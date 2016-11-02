/**
 * @file src/program/game/entity/npc/state/NPCAttacking.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#include "../NPCAttacking.hpp"
#include <iostream>

namespace rr
{

    NPCState*
    NPCAttacking::update(sf::Time& delta, NPC* npc)
    {
        //if (npc->m_body.isPlaying())
        //    return nullptr;

        return &hunting;
    }

    NPCState*
    NPCAttacking::react(Level* level, NPC* npc, Player* player)
    { return nullptr; }

    sf::String
    NPCAttacking::toString() const
    { return "ATTACKING"; }

}