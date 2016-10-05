/**
 * @file src/program/game/entities/npc/AI.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML
 */

#ifndef NPC_AI_HPP
#define NPC_AI_HPP

#include "../../Entity.hpp"

namespace rr
{

    class AI
    {
        public: ////////////////////////////////////////////////////////////////////////
                /// \brief Tells if the NPC can move towards the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual bool canMoveTowards(Entity*, NPC*, int[]) const = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Moves the NPC towards the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual void moveTowards(Entity*, NPC*) = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Tells if the NPC can move away from the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual bool canMoveAwayFrom(Entity*, NPC*) const = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Moves the NPC away from the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual void moveAwayFrom(Entity*, NPC*) = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Tells if the NPC can escape from the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual bool canEscapeFrom(Entity*, NPC*) const = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Makes the NPC escape from the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual void escapeFrom(Entity*, NPC*) = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Tells if the NPC can attack the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual bool canAttack(Entity*, NPC*) const = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Makes the NPC attack the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual void attack(Entity*, NPC*) = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Tells if the NPC is too close to the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual bool tooCloseTo(Entity*, NPC*) const = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Tells if the NPC is too far from the entity.
                ////////////////////////////////////////////////////////////////////////
        virtual bool tooFarFrom(Entity*, NPC*) const = 0;

                ////////////////////////////////////////////////////////////////////////
                /// \brief Makes the NPC stand still.
                ////////////////////////////////////////////////////////////////////////
        virtual void standStill() = 0;
    };

}

#endif // NPC_AI_HPP