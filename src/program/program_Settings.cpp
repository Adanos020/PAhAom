/**
 * @file src/program/program_Settings.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "program.hpp"
#include "funcs/files.hpp"
#include "funcs/keys.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

namespace rr {

    void Settings::print() {
        std::cout << "+========PARAMETER========|===========VALUE===========+\n";
        std::cout << "+-------------------Game settings---------------------+\n";
        std::cout << "|lang                     |" << game.language                                     << std::setw(29-game.language                                         .size()) << "|\n";
        std::cout << "+-----------------Graphical settings------------------+\n";
        std::cout << "|width                    |" << graphics.resolution.x                             << std::setw(29-std::to_string(graphics.resolution.x)                 .size()) << "|\n";
        std::cout << "|height                   |" << graphics.resolution.y                             << std::setw(29-std::to_string(graphics.resolution.y)                 .size()) << "|\n";
        std::cout << "|fullscreen               |" << graphics.fullscreen                               << std::setw(29-std::to_string(graphics.fullscreen)                   .size()) << "|\n";
        std::cout << "|vsync                    |" << graphics.vsync                                    << std::setw(29-std::to_string(graphics.vsync)                        .size()) << "|\n";
        std::cout << "|antialiasing             |" << graphics.csettings.antialiasingLevel              << std::setw(29-std::to_string(graphics.csettings.antialiasingLevel)  .size()) << "|\n";
        std::cout << "|depth_bits               |" << graphics.csettings.depthBits                      << std::setw(29-std::to_string(graphics.csettings.depthBits)          .size()) << "|\n";
        std::cout << "|stencil_bits             |" << graphics.csettings.stencilBits                    << std::setw(29-std::to_string(graphics.csettings.stencilBits)        .size()) << "|\n";
        std::cout << "+-----------------------Audio-------------------------+\n";
        std::cout << "|music_volume             |" << sound.music_volume                                << std::setw(29-std::to_string((int)sound.music_volume)               .size()) << "|\n";
        std::cout << "|effects_volume           |" << sound.effects_volume                              << std::setw(29-std::to_string((int)sound.effects_volume)             .size()) << "|\n";
        std::cout << "|music_muted              |" << sound.music_muted                                 << std::setw(29-std::to_string(sound.music_muted)                     .size()) << "|\n";
        std::cout << "|effects_muted            |" << sound.effects_muted                               << std::setw(29-std::to_string(sound.effects_muted)                   .size()) << "|\n";
        std::cout << "+----------------------Controls-----------------------+\n";
        std::cout << "|move_up                  |" << getKeyName(keys.move_up)          .toAnsiString() << std::setw(29-getKeyName(keys.move_up)          .toAnsiString()     .size()) << "|\n";
        std::cout << "|move_down                |" << getKeyName(keys.move_down)        .toAnsiString() << std::setw(29-getKeyName(keys.move_down)        .toAnsiString()     .size()) << "|\n";
        std::cout << "|move_left                |" << getKeyName(keys.move_left)        .toAnsiString() << std::setw(29-getKeyName(keys.move_left)        .toAnsiString()     .size()) << "|\n";
        std::cout << "|move_right               |" << getKeyName(keys.move_right)       .toAnsiString() << std::setw(29-getKeyName(keys.move_right)       .toAnsiString()     .size()) << "|\n";
        std::cout << "|interact                 |" << getKeyName(keys.interact)         .toAnsiString() << std::setw(29-getKeyName(keys.interact)         .toAnsiString()     .size()) << "|\n";
        std::cout << "|attack                   |" << getKeyName(keys.attack)           .toAnsiString() << std::setw(29-getKeyName(keys.attack)           .toAnsiString()     .size()) << "|\n";
        std::cout << "|open_inventory           |" << getKeyName(keys.open_inventory)   .toAnsiString() << std::setw(29-getKeyName(keys.open_inventory)   .toAnsiString()     .size()) << "|\n";
        std::cout << "|open_attributes          |" << getKeyName(keys.open_attributes)  .toAnsiString() << std::setw(29-getKeyName(keys.open_attributes)  .toAnsiString()     .size()) << "|\n";
        std::cout << "|open_quests              |" << getKeyName(keys.open_quests)      .toAnsiString() << std::setw(29-getKeyName(keys.open_quests)      .toAnsiString()     .size()) << "|\n";
        std::cout << "|open_map                 |" << getKeyName(keys.open_map)         .toAnsiString() << std::setw(29-getKeyName(keys.open_map)         .toAnsiString()     .size()) << "|\n";
        std::cout << "|open_bookOfSpells        |" << getKeyName(keys.open_bookOfSpells).toAnsiString() << std::setw(29-getKeyName(keys.open_bookOfSpells).toAnsiString()     .size()) << "|\n";
        std::cout << "|useslot_1                |" << getKeyName(keys.useslot_1)        .toAnsiString() << std::setw(29-getKeyName(keys.useslot_1)        .toAnsiString()     .size()) << "|\n";
        std::cout << "|useslot_2                |" << getKeyName(keys.useslot_2)        .toAnsiString() << std::setw(29-getKeyName(keys.useslot_2)        .toAnsiString()     .size()) << "|\n";
        std::cout << "|useslot_3                |" << getKeyName(keys.useslot_3)        .toAnsiString() << std::setw(29-getKeyName(keys.useslot_3)        .toAnsiString()     .size()) << "|\n";
        std::cout << "|useslot_4                |" << getKeyName(keys.useslot_4)        .toAnsiString() << std::setw(29-getKeyName(keys.useslot_4)        .toAnsiString()     .size()) << "|\n";
        std::cout << "|useslot_5                |" << getKeyName(keys.useslot_5)        .toAnsiString() << std::setw(29-getKeyName(keys.useslot_5)        .toAnsiString()     .size()) << "|\n";
        std::cout << "+-----------------------------------------------------+\n";
    }

    void Settings::save() {
        std::cout << ">Saving the settings...\n";

        std::ofstream oconfig("config.cfg");
        oconfig.clear();

        oconfig << ";---------------;\n";
        oconfig << ";-game settings-;\n";
        oconfig << "lang:\t\t"           + game.language                                       +"\n";
        oconfig << ";---------------;\n";
        oconfig << ";video  settings;\n";
        oconfig << ";----screen-----;\n";
        oconfig << "width:\t\t"          + std::to_string(graphics.resolution.x               )+"\n";
        oconfig << "height:\t\t"         + std::to_string(graphics.resolution.y               )+"\n";
        oconfig << "fullscreen:\t"       + std::to_string(graphics.fullscreen                 )+"\n";
        oconfig << "vsync:\t\t"          + std::to_string(graphics.vsync                      )+"\n";
        oconfig << ";---graphics----;\n";
        oconfig << "antialiasing:\t"     + std::to_string(graphics.csettings.antialiasingLevel)+"\n";
        oconfig << "depth_bits:\t"       + std::to_string(graphics.csettings.depthBits        )+"\n";
        oconfig << "stencil_bits:\t"     + std::to_string(graphics.csettings.stencilBits      )+"\n";
        oconfig << ";---------------;\n";
        oconfig << ";audio  settings;\n";
        oconfig << "music_volume:\t"     + std::to_string(sound.music_volume                  )+"\n";
        oconfig << "effects_volume:\t"   + std::to_string(sound.effects_volume                )+"\n";
        oconfig << "music_muted:\t"      + std::to_string(sound.music_muted                   )+"\n";
        oconfig << "effects_muted:\t"    + std::to_string(sound.effects_muted                 )+"\n";
        oconfig << ";---------------;\n";
        oconfig << ";--key binding--;\n";
        oconfig << ";---movement----;\n";
        oconfig << "move_up:\t"          + std::to_string(keys.move_up                        )+"\n";
        oconfig << "move_down:\t"        + std::to_string(keys.move_down                      )+"\n";
        oconfig << "move_left:\t"        + std::to_string(keys.move_left                      )+"\n";
        oconfig << "move_right:\t"       + std::to_string(keys.move_right                     )+"\n";
        oconfig << ";----actions----;\n";
        oconfig << "interact:\t"         + std::to_string(keys.interact                       )+"\n";
        oconfig << "attack:\t\t"         + std::to_string(keys.attack                         )+"\n";
        oconfig << ";---open menus--;\n";
        oconfig << "open_inventory:\t"   + std::to_string(keys.open_inventory                 )+"\n";
        oconfig << "open_attributes: "   + std::to_string(keys.open_attributes                )+"\n";
        oconfig << "open_quests:\t"      + std::to_string(keys.open_quests                    )+"\n";
        oconfig << "open_map:\t"         + std::to_string(keys.open_map                       )+"\n";
        oconfig << "open_bookOfSpells:\t"+ std::to_string(keys.open_bookOfSpells              )+"\n";
        oconfig << ";---use slots---;\n";
        oconfig << "useslot_1:\t"        + std::to_string(keys.useslot_1                      )+"\n";
        oconfig << "useslot_2:\t"        + std::to_string(keys.useslot_2                      )+"\n";
        oconfig << "useslot_3:\t"        + std::to_string(keys.useslot_3                      )+"\n";
        oconfig << "useslot_4:\t"        + std::to_string(keys.useslot_4                      )+"\n";
        oconfig << "useslot_5:\t"        + std::to_string(keys.useslot_5                      )+"\n";
        oconfig << ";---------------;\n";

        oconfig.close();
    }

    bool Settings::load() {
        try {
            std::ifstream iconfig("config.cfg");
            if ( !iconfig.good()
                ) throw "File not found";
            std::cout << ">Loading a config file...\n";

            while (!iconfig.eof()) {
                std::string param;
                int keyCode;
                iconfig >> param;

                if (param[0] == ';' || param == "") {
                    std::getline(iconfig, param);
                    continue;
                } else {
                    if      (param == "lang:"             )   iconfig >>        game.language                        ;
                    else if (param == "width:"            )   readFile(iconfig, graphics.resolution.x               );
                    else if (param == "height:"           )   readFile(iconfig, graphics.resolution.y               );
                    else if (param == "fullscreen:"       )   readFile(iconfig, graphics.fullscreen                 );
                    else if (param == "vsync:"            )   readFile(iconfig, graphics.vsync                      );
                    else if (param == "antialiasing:"     )   readFile(iconfig, graphics.csettings.antialiasingLevel);
                    else if (param == "depth_bits:"       )   readFile(iconfig, graphics.csettings.depthBits        );
                    else if (param == "stencil_bits:"     )   readFile(iconfig, graphics.csettings.stencilBits      );
                    else if (param == "music_volume:"     )   readFile(iconfig, sound.music_volume                  );
                    else if (param == "effects_volume:"   )   readFile(iconfig, sound.effects_volume                );
                    else if (param == "music_muted:"      )   readFile(iconfig, sound.music_muted                   );
                    else if (param == "effects_muted:"    )   readFile(iconfig, sound.effects_muted                 );
                    else if (param == "move_up:"          ) { readFile(iconfig, keyCode                             ); keys.move_up           = (sf::Keyboard::Key)keyCode; }
                    else if (param == "move_down:"        ) { readFile(iconfig, keyCode                             ); keys.move_down         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "move_left:"        ) { readFile(iconfig, keyCode                             ); keys.move_left         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "move_right:"       ) { readFile(iconfig, keyCode                             ); keys.move_right        = (sf::Keyboard::Key)keyCode; }
                    else if (param == "interact:"         ) { readFile(iconfig, keyCode                             ); keys.interact          = (sf::Keyboard::Key)keyCode; }
                    else if (param == "attack:"           ) { readFile(iconfig, keyCode                             ); keys.attack            = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_inventory:"   ) { readFile(iconfig, keyCode                             ); keys.open_inventory    = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_attributes:"  ) { readFile(iconfig, keyCode                             ); keys.open_attributes   = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_quests:"      ) { readFile(iconfig, keyCode                             ); keys.open_quests       = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_map:"         ) { readFile(iconfig, keyCode                             ); keys.open_map          = (sf::Keyboard::Key)keyCode; }
                    else if (param == "open_bookOfSpells:") { readFile(iconfig, keyCode                             ); keys.open_bookOfSpells = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_1:"        ) { readFile(iconfig, keyCode                             ); keys.useslot_1         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_2:"        ) { readFile(iconfig, keyCode                             ); keys.useslot_2         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_3:"        ) { readFile(iconfig, keyCode                             ); keys.useslot_3         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_4:"        ) { readFile(iconfig, keyCode                             ); keys.useslot_4         = (sf::Keyboard::Key)keyCode; }
                    else if (param == "useslot_5:"        ) { readFile(iconfig, keyCode                             ); keys.useslot_5         = (sf::Keyboard::Key)keyCode; }
                    else                                  throw "Wrong parameter";
                }
            }
            iconfig.close();
            std::cout << ">Done.\n";
        } catch (...) {
            std::cout << "!Error loading config.cfg!\n";
            std::cout << ">Creating a new config file...\n";

            game.language                        = "en";
            graphics.resolution.x                = 1280;
            graphics.resolution.y                = 720;
            graphics.fullscreen                  = false;
            graphics.vsync                       = true;
            graphics.csettings.antialiasingLevel = 4;
            graphics.csettings.depthBits         = 24;
            graphics.csettings.stencilBits       = 8;
            sound.music_volume                   = 50.f;
            sound.effects_volume                 = 50.f;
            sound.music_muted                    = false;
            sound.effects_muted                  = false;
            keys.move_up                         = sf::Keyboard::W;
            keys.move_down                       = sf::Keyboard::S;
            keys.move_left                       = sf::Keyboard::A;
            keys.move_right                      = sf::Keyboard::D;
            keys.interact                        = sf::Keyboard::E;
            keys.attack                          = sf::Keyboard::Space;
            keys.open_inventory                  = sf::Keyboard::Tab;
            keys.open_attributes                 = sf::Keyboard::B;
            keys.open_quests                     = sf::Keyboard::N;
            keys.open_map                        = sf::Keyboard::M;
            keys.open_bookOfSpells               = sf::Keyboard::V;
            keys.useslot_1                       = sf::Keyboard::Num1;
            keys.useslot_2                       = sf::Keyboard::Num2;
            keys.useslot_3                       = sf::Keyboard::Num3;
            keys.useslot_4                       = sf::Keyboard::Num4;
            keys.useslot_5                       = sf::Keyboard::Num5;

            save ();
        }
        return true;
    }

}
