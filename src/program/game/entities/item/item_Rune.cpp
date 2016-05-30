/**
 * @file src/program/game/item/item_Rune.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "item_Rune.hpp"
#include "../../../program.hpp"
#include "../../../funcs/images.hpp"

extern rr::Resources resources;
extern int           spellSymbols[11];

namespace rr {

    Rune::Rune(Type type, int am, sf::Vector2i pos)
    : Discoverable(),
      type_       (type) {

        amount_     = am;
        disposable_ = true;
        stackable_  = true;
        ID_         = 39+type_;
        iconIndex_  = 48;

        switch (spellSymbols[type_]) {
            case  0: name_ = resources.dictionary["item.spell.symbol.shcha"  ]; break;
            case  1: name_ = resources.dictionary["item.spell.symbol.jus"    ]; break;
            case  2: name_ = resources.dictionary["item.spell.symbol.jes"    ]; break;
            case  3: name_ = resources.dictionary["item.spell.symbol.ef"     ]; break;
            case  4: name_ = resources.dictionary["item.spell.symbol.ju"     ]; break;
            case  5: name_ = resources.dictionary["item.spell.symbol.psi"    ]; break;
            case  6: name_ = resources.dictionary["item.spell.symbol.de"     ]; break;
            case  7: name_ = resources.dictionary["item.spell.symbol.omega"  ]; break;
            case  8: name_ = resources.dictionary["item.spell.symbol.je"     ]; break;
            case  9: name_ = resources.dictionary["item.spell.symbol.zhe"    ]; break;
            case 10: name_ = resources.dictionary["item.spell.symbol.be"     ]; break;
            case 11: name_ = resources.dictionary["item.spell.symbol.izhitsa"]; break;
        }
        description_ = resources.dictionary["item.spell.description.unknown"];

        switch (type_) {
            case HEAL         : discoveredName_        = resources.dictionary["item.spell.type.heal"               ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.heal"        ]; break;
            case FIREBOLT     : discoveredName_        = resources.dictionary["item.spell.type.firebolt"           ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.firebolt"    ]; break;
            case LIGHTNING    : discoveredName_        = resources.dictionary["item.spell.type.lightning"          ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.lightning"   ]; break;
            case ICE_BULLET   : discoveredName_        = resources.dictionary["item.spell.type.iceBullet"          ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.iceBullet"   ]; break;
            case TELEPORT     : discoveredName_        = resources.dictionary["item.spell.type.teleport"           ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.teleport"    ]; break;
            case FIRE_RAIN    : discoveredName_        = resources.dictionary["item.spell.type.fireRain"           ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.fireRain"    ]; break;
            case STORM        : discoveredName_        = resources.dictionary["item.spell.type.storm"              ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.storm"       ]; break;
            case ICE_WAVE     : discoveredName_        = resources.dictionary["item.spell.type.iceWave"            ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.iceWave"     ]; break;
            case TIME_FREEZING: discoveredName_        = resources.dictionary["item.spell.type.timeFreezing"       ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.timeFreezing"]; break;
            case IDENTIFY     : discoveredName_        = resources.dictionary["item.spell.type.identify"           ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.identify"    ]; break;
            case UNCURSE      : discoveredName_        = resources.dictionary["item.spell.type.uncurse"            ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.uncurse"     ]; break;
            case TELEKINESIS  : discoveredName_        = resources.dictionary["item.spell.type.telekinesis"        ];
                                discoveredDescription_ = resources.dictionary["item.spell.description.telekinesis" ]; break;
        }

        int icons[] = { (int)iconIndex_, 64+(int)spellSymbols[type_] };

        setIcon(body_, 2, icons);
        setPosition(pos);
    }

    void Rune::reveal() {
        discovered_  = true;
        name_        = discoveredName_;
        description_ = discoveredDescription_;
    }

    void Rune::draw(sf::RenderWindow& rw) {
        rw.draw(body_, &resources.texture.items);
    }

    void Rune::setPosition(sf::Vector2i pos) {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void Rune::setRealPosition(sf::Vector2f pos) {
        body_[0].position = pos;
        body_[1].position = sf::Vector2f(pos.x+80, pos.y   );
        body_[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        body_[3].position = sf::Vector2f(pos.x   , pos.y+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

}