/**
 * @file src/main.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <SFML/Graphics.hpp>

#include "program/program.hpp"

rr::Resources resources;
rr::Settings  settings;
rr::Subject   subject;
sf::Color     itemColors[9];
int           spellSymbols[12];

int main() {
    auto p = new rr::Program();
    delete p;
    
    return EXIT_SUCCESS;
}
