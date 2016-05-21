/**
 * @file src/main.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "program/program.hpp"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

rr::Resources  resources;
rr::Settings   settings;
rr::Subject    subject;
sf::Color      itemColors[9];

int main() {
    srand(time(0));
    auto p = new rr::Program();

    delete p;
    return EXIT_SUCCESS;
}
