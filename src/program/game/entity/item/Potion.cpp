/**
 * @file src/program/game/item/Potion.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "Potion.hpp"

#include "../../../Resources.hpp"

#include "../../../funcs/images.hpp"
#include "../../../funcs/files.hpp"

extern sf::Color itemColors[9];

namespace rr {

    bool Potion::identified_[9] = { false, false, false, false, false, false, false, false, false };

    Potion::Potion(Type e, Size s, int am, sf::Vector2u pos) :
      type_(e),
      size_(s)
    {
        amount_     = am;
        
        initialize();
        setGridPosition(pos);
    }

    Potion::Potion(Potion const& copy) :
      type_(copy.type_),
      size_(copy.size_)
    {
        amount_     = copy.amount_;
        disposable_ = copy.disposable_;
        stackable_  = copy.stackable_;
        ID_         = copy.ID_;
        iconIndex_  = copy.iconIndex_;
        body_       = copy.body_;
    }

    void Potion::initialize() {
        disposable_ = true;
        stackable_  = true;
        cursed_     = false;
        ID_         = 100 + type_*10 + size_;
        iconIndex_  = 3-size_;

        int icons[] = { (int)iconIndex_, (int)iconIndex_+16 };

        setIcon (body_, 2, icons);
        setColor(body_, 1, itemColors[type_]);
    }

    sf::String Potion::getName() const {
        if (!identified_[type_]) {
                 if (itemColors[type_] == sf::Color::Red          ) return Resources::dictionary["item.potion.color.red"    ];
            else if (itemColors[type_] == sf::Color::Blue         ) return Resources::dictionary["item.potion.color.blue"   ];
            else if (itemColors[type_] == sf::Color(32, 32, 0)    ) return Resources::dictionary["item.potion.color.brown"  ];
            else if (itemColors[type_] == sf::Color::Green        ) return Resources::dictionary["item.potion.color.green"  ];
            else if (itemColors[type_] == sf::Color::Cyan         ) return Resources::dictionary["item.potion.color.cyan"   ];
            else if (itemColors[type_] == sf::Color(255, 172, 172)) return Resources::dictionary["item.potion.color.pink"   ];
            else if (itemColors[type_] == sf::Color::Magenta      ) return Resources::dictionary["item.potion.color.magenta"];
            else if (itemColors[type_] == sf::Color::Yellow       ) return Resources::dictionary["item.potion.color.yellow" ];
            else if (itemColors[type_] == sf::Color::White        ) return Resources::dictionary["item.potion.color.white"  ];
        }
        else {
            switch (type_) {
                case HEALING:      return Resources::dictionary["item.potion.effect.healing"     ];
                case MAGIC:        return Resources::dictionary["item.potion.effect.magic"       ];
                case STRENGTH:     return Resources::dictionary["item.potion.effect.strength"    ];
                case DEXTERITY:    return Resources::dictionary["item.potion.effect.dexterity"   ];
                case SPEED:        return Resources::dictionary["item.potion.effect.speed"       ];
                case REGENERATION: return Resources::dictionary["item.potion.effect.regeneration"];
                case POISON:       return Resources::dictionary["item.potion.effect.poison"      ];
                case SLOWNESS:     return Resources::dictionary["item.potion.effect.slowness"    ];
                case WEAKNESS:     return Resources::dictionary["item.potion.effect.weakness"    ];
            }
        }
        return "";
    }

    sf::String Potion::getDescription() const {
        if ( !identified_[type_]
            ) return Resources::dictionary["item.potion.description.unknown"];
        else {
            switch (type_) {
                case HEALING     : return Resources::dictionary["item.potion.description.healing"     ];
                case MAGIC       : return Resources::dictionary["item.potion.description.magic"       ];
                case STRENGTH    : return Resources::dictionary["item.potion.description.strength"    ];
                case DEXTERITY   : return Resources::dictionary["item.potion.description.dexterity"   ];
                case SPEED       : return Resources::dictionary["item.potion.description.speed"       ];
                case REGENERATION: return Resources::dictionary["item.potion.description.regeneration"];
                case POISON      : return Resources::dictionary["item.potion.description.poison"      ];
                case SLOWNESS    : return Resources::dictionary["item.potion.description.slowness"    ];
                case WEAKNESS    : return Resources::dictionary["item.potion.description.weakness"    ];
            }
        }
        return "";
    }

    void Potion::setGridPosition(sf::Vector2u pos) {
        body_[0].position = (sf::Vector2f)pos*80.f;
        body_[1].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f   );
        body_[2].position =  sf::Vector2f(pos.x*80.f+80, pos.y*80.f+80);
        body_[3].position =  sf::Vector2f(pos.x*80.f   , pos.y*80.f+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    void Potion::setPosition(sf::Vector2f pos) {
        body_[0].position = pos;
        body_[1].position = sf::Vector2f(pos.x+80, pos.y   );
        body_[2].position = sf::Vector2f(pos.x+80, pos.y+80);
        body_[3].position = sf::Vector2f(pos.x   , pos.y+80);

        body_[4].position = body_[0].position;
        body_[5].position = body_[1].position;
        body_[6].position = body_[2].position;
        body_[7].position = body_[3].position;
    }

    std::ifstream& Potion::operator<<(std::ifstream& file) {
        sf::Vector2u position;
        int type, size;

        try {
            readFile <unsigned> (file, position.x);
            readFile <unsigned> (file, position.y);
            readFile <   int  > (file, amount_);
            readFile <   int  > (file, type);
            readFile <   int  > (file, size);
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        type_ = (Type) type;
        size_ = (Size) size;

        initialize();
        setGridPosition(position);

        return file;
    }

    std::ofstream& Potion::operator>>(std::ofstream& file) {
        file << 5                                  << ' '
             << (unsigned) body_[0].position.x/80u << ' '
             << (unsigned) body_[0].position.y/80u << ' '
             << amount_                            << ' '
             << type_                              << ' '
             << size_;

        return file;
    }

}
