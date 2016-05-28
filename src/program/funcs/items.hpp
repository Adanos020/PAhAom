/**
 * @file src/program/game/item/items.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef item_funcs_hpp
#define item_funcs_hpp

#include <iostream>

#include "../game/entities/item/item.hpp"

namespace rr {

/// Returns an instance of the Item class depending on the given ID and amount
    inline Item* getItemFromID(int ID, int amount) {
        switch (ID) {
        /* COIN */
        case   1: return new Coin      (Coin::GOLDEN                , Coin::SMALL         , amount);
        case   2: return new Coin      (Coin::SILVER                , Coin::SMALL         , amount);
        case   3: return new Coin      (Coin::BRONZE                , Coin::SMALL         , amount);
        case   4: return new Coin      (Coin::GOLDEN                , Coin::BIG           , amount);
        case   5: return new Coin      (Coin::SILVER                , Coin::BIG           , amount);
        case   6: return new Coin      (Coin::BRONZE                , Coin::BIG           , amount);

        /* COLD WEAPON */
        case  10: return new ColdWeapon(ColdWeapon::KNIFE                                 , amount);
        case  11: return new ColdWeapon(ColdWeapon::DAGGER                                , amount);
        case  12: return new ColdWeapon(ColdWeapon::SWORD                                 , amount);
        case  13: return new ColdWeapon(ColdWeapon::SERRATED_SWORD                        , amount);
        case  14: return new ColdWeapon(ColdWeapon::AXE                                   , amount);
        case  15: return new ColdWeapon(ColdWeapon::DOUBLE_AXE                            , amount);
        case  16: return new ColdWeapon(ColdWeapon::HALBERD                               , amount);
        case  17: return new ColdWeapon(ColdWeapon::SPEAR                                 , amount);
        case  18: return new ColdWeapon(ColdWeapon::LANCE                                 , amount);
        case  19: return new ColdWeapon(ColdWeapon::PIQUE                                 , amount);
        case  20: return new ColdWeapon(ColdWeapon::LONG_STICK                            , amount);
        case  21: return new ColdWeapon(ColdWeapon::CLUB                                  , amount);
        case  22: return new ColdWeapon(ColdWeapon::HAMMER                                , amount);

        /* BOOKS */
        case  30: return new Book      (Book::CRAFTING                                    , amount);
        case  31: return new Book      (Book::ALCHEMY                                     , amount);
        case  32: return new Book      (Book::COLD_WEAPON_MASTERY                         , amount);
        case  33: return new Book      (Book::RANGED_WEAPON_MASTERY                       , amount);
        case  34: return new Book      (Book::EAGLE_EYE                                   , amount);
        case  35: return new Book      (Book::MANA_REGEN                                  , amount);
        case  36: return new Book      (Book::HEALTH_REGEN                                , amount);
        case  37: return new Book      (Book::FASTER_LEARNING                             , amount);
        case  38: return new Book      (Book::SPELLS_BOOK                                 , amount);

        /* SPELLS */
        case  39: return new Spell     (Spell::HEAL                                       , amount);
        case  40: return new Spell     (Spell::FIREBOLT                                   , amount);
        case  41: return new Spell     (Spell::LIGHTNING                                  , amount);
        case  42: return new Spell     (Spell::ICE_BULLET                                 , amount);
        case  43: return new Spell     (Spell::TELEPORT                                   , amount);
        case  44: return new Spell     (Spell::FIRE_RAIN                                  , amount);
        case  45: return new Spell     (Spell::STORM                                      , amount);
        case  46: return new Spell     (Spell::ICE_WAVE                                   , amount);
        case  47: return new Spell     (Spell::TIME_FREEZING                              , amount);
        case  48: return new Spell     (Spell::IDENTIFY                                   , amount);
        case  49: return new Spell     (Spell::UNCURSE                                    , amount);

        /* POTIONS */
        case 100: return new Potion    (Potion::Effect::HEALING     , Potion::Size::SMALL , amount);
        case 110: return new Potion    (Potion::Effect::HEALING     , Potion::Size::MEDIUM, amount);
        case 120: return new Potion    (Potion::Effect::HEALING     , Potion::Size::BIG   , amount);

        case 101: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::SMALL , amount);
        case 111: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::MEDIUM, amount);
        case 121: return new Potion    (Potion::Effect::MAGIC       , Potion::Size::BIG   , amount);

        case 102: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::SMALL , amount);
        case 112: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::MEDIUM, amount);
        case 122: return new Potion    (Potion::Effect::STRENGTH    , Potion::Size::BIG   , amount);

        case 103: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::SMALL , amount);
        case 113: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::MEDIUM, amount);
        case 123: return new Potion    (Potion::Effect::DEXTERITY   , Potion::Size::BIG   , amount);

        case 104: return new Potion    (Potion::Effect::SPEED       , Potion::Size::SMALL , amount);
        case 114: return new Potion    (Potion::Effect::SPEED       , Potion::Size::MEDIUM, amount);
        case 124: return new Potion    (Potion::Effect::SPEED       , Potion::Size::BIG   , amount);

        case 105: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::SMALL , amount);
        case 115: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::MEDIUM, amount);
        case 125: return new Potion    (Potion::Effect::REGENERATION, Potion::Size::BIG   , amount);

        case 106: return new Potion    (Potion::Effect::POISON      , Potion::Size::SMALL , amount);
        case 116: return new Potion    (Potion::Effect::POISON      , Potion::Size::MEDIUM, amount);
        case 126: return new Potion    (Potion::Effect::POISON      , Potion::Size::BIG   , amount);

        case 107: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::SMALL , amount);
        case 117: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::MEDIUM, amount);
        case 127: return new Potion    (Potion::Effect::SLOWNESS    , Potion::Size::BIG   , amount);

        case 108: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::SMALL , amount);
        case 118: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::MEDIUM, amount);
        case 128: return new Potion    (Potion::Effect::WEAKNESS    , Potion::Size::BIG   , amount);

        /*unknown ID?*/
        default : std::cout << "UNKNOWN ITEM ID" << '\n'; return nullptr;
        }

    }

}

#endif // item_funcs_hpp
