/**
 * @file src/program/game/entity/npc/Teacher.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef NPC_TEACHER_HPP
#define NPC_TEACHER_HPP

#include "NPC.hpp"

namespace rr {

    class Teacher : public NPC {
    private: sf::Animation standingStill_;
             
             virtual void           initialize()                   override;
    
    public:  enum Type {
                 SWORDSMAN,
                 SHARPSHOOTER,
                 CARPENTER,
                 MAGE,
                 KUNG_FU_MASTER
             } type_;
         
             Teacher(Type = SWORDSMAN);
             Teacher(Teacher const&);
         
             virtual Entity*        clone       () const             override { return new Teacher(*this); }
         
             virtual void           handleDamage(int damage)         override;

             virtual void           talk        ();
             virtual void           update      (sf::Time timeStep)  override;
         
             virtual std::ifstream& operator<<  (std::ifstream&)     override;
             virtual std::ofstream& operator>>  (std::ofstream&)     override;
    };

}

#endif // NPC_TEACHER_HPP
