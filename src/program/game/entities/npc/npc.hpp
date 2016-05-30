/**
 * @file src/program/game/entities/npc/npc.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef npc_hpp
#define npc_hpp

#include "../entities.hpp"
#include "../../../../../lib/AnimatedSprite.hpp"
#include "../../../gui/gui.hpp"

namespace rr {

    class NPC : public Entity {
    protected:
        sf::AnimatedSprite body_;
        sf::Animation      standingStill_;
        sf::Animation*     currentAnimation_;
    public:
        virtual ~NPC() {}

        virtual void          talk            ()               = 0;
        virtual void          update          (float timeStep) = 0;

        virtual void          draw            (sf::RenderWindow& rw) override { rw.draw(body_); }
        virtual void          setPosition     (sf::Vector2i pos)     override { body_.setPosition((sf::Vector2f)pos*80.f); }
        virtual void          setRealPosition (sf::Vector2f pos)     override { body_.setPosition(pos); }

        virtual bool          intersects      (Entity* e) const      override { return e->getBounds().intersects(getBounds()); }
        virtual sf::FloatRect getBounds       ()          const      override { return body_.getGlobalBounds(); }
        virtual sf::Vector2i  getPosition     ()          const      override { return (sf::Vector2i)body_.getPosition()/80; }
        virtual sf::Vector2f  getRealPosition ()          const      override { return body_.getPosition(); }
    };

    class Teacher : public NPC {
    public:
        enum Type {
            SWORDSMAN,
            SHARPSHOOTER,
            CARPENTER,
            MAGE,
            KUNG_FU_CHAMPION
        } type_;

         Teacher(Type);
        ~Teacher() {}

        virtual void talk  ()               override;
        virtual void update(float timeStep) override;
    };

    class Merchant : public NPC {
    public:
        enum Type {
            POTION_SELLER,
            BOOK_SELLER,
            WEAPON_SELLER,
            ARMOR_SELLER,
            ARTIFACT_SELLER
        } type_;

         Merchant(Type);
        ~Merchant() {}

        virtual void talk  ()               override;
        virtual void update(float timeStep) override;
    };

    class QuestGiver : public NPC {
    public:
        enum Type {
            NONE_YET
        } type_;

         QuestGiver(Type);
        ~QuestGiver() {}

        virtual void talk  ()               override;
        virtual void update(float timeStep) override;
    };

}

#endif // npc_hpp
