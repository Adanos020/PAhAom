/**
 * @file src/program/game/shadowmap/ShadowMap.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <iostream>

#include "../../funcs/files.hpp"
#include "../../Resources.hpp"

#include "ShadowMap.hpp"

namespace rr {

    ShadowMap::ShadowMap(sf::Vector2u size) :
      size_(size)
    {
        shadowImage_.create(3*size_.x, 3*size_.y);

        shadowTexture_.setSmooth(true);
        
        shadowSprite_.resize(4);
        shadowSprite_.setPrimitiveType(sf::Quads);

        shadowSprite_[0].position = sf::Vector2f(0        , 0);
        shadowSprite_[1].position = sf::Vector2f(80*size.x, 0);
        shadowSprite_[2].position = sf::Vector2f(80*size.x, 80*size.y);
        shadowSprite_[3].position = sf::Vector2f(0        , 80*size.y);

        for (unsigned i=0; i<size_.x*size_.y; ++i) {
            discovered_[i] = false;
        }
    }

    void ShadowMap::fillCell(unsigned x, unsigned y, char id) {
        x *= 3; // setting the pixel coordinates to
        y *= 3; // the top-left edge of the cell

        for (unsigned i=0; i<3; ++i) {
            for (unsigned j=0; j<3; ++j) {
                cellIDs_[x+i + (y+j)*size_.x*3] = id;
            }
        }
    }

    bool ShadowMap::isFilled(unsigned x, unsigned y, char id) const {
        if (  x < 0 || x > size_.x-1
           || y < 0 || y > size_.y-1
            ) return false;

        unsigned tx = 3*x, ty = 3*y;

        bool filled = true;

        for (unsigned i=0; i<3; ++i) {
            for (unsigned j=0; j<3; ++j) {
                if (cellIDs_[tx+i + (ty+j)*size_.x*3] == id) {
                    filled = false;
                    break;
                } 
            }
            if ( !filled
                ) break;
        }

        return filled;
    }

    void ShadowMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &shadowTexture_;
        target.draw(shadowSprite_, states);
    }

    void ShadowMap::setLit(unsigned x, unsigned y) {
        discovered_[x + y*size_.x] = true;

        unsigned tx = 3*x + 1, ty = 3*y + 1;

        cellIDs_[tx + ty*size_.x*3] = 2;

        if (x < size_.x-1) {
            if (y > 0) {
                if (cellIDs_[tx+3 + (ty-3)*size_.x*3] == 2) {  // TOP RIGHT
                    cellIDs_[tx+1 + (ty-1)*size_.x*3] =  2;
                    cellIDs_[tx+1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty-1)*size_.x*3] =  2;

                    cellIDs_[tx+2 + (ty-2)*size_.x*3] =  2;
                }
            }

            if (y < size_.y-1) {
                if (cellIDs_[tx+3 + (ty+3)*size_.x*3] == 2) {  // BOTTOM RIGHT
                    cellIDs_[tx+1 + (ty+1)*size_.x*3] =  2;
                    cellIDs_[tx+1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty+1)*size_.x*3] =  2;

                    cellIDs_[tx+2 + (ty+2)*size_.x*3] =  2;
                }
            }

            if (cellIDs_[tx+3 + ty*size_.x*3] == 2) {        // RIGHT
                cellIDs_[tx+1 + ty*size_.x*3] =  2;
                cellIDs_[tx+2 + ty*size_.x*3] =  2;
            }
        }

        if (x > 0) {
            if (y > 0) {
                if (cellIDs_[tx-3 + (ty-3)*size_.x*3] == 2) {  // TOP LEFT
                    cellIDs_[tx-1 + (ty-1)*size_.x*3] =  2;
                    cellIDs_[tx-1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty-1)*size_.x*3] =  2;

                    cellIDs_[tx-2 + (ty-2)*size_.x*3] =  2;
                }
            }

            if (y < size_.y-1) {
                if (cellIDs_[tx-3 + (ty+3)*size_.x*3] == 2) {  // BOTTOM LEFT
                    cellIDs_[tx-1 + (ty+1)*size_.x*3] =  2;
                    cellIDs_[tx-1 + ( ty )*size_.x*3] =  2;
                    cellIDs_[ tx  + (ty+1)*size_.x*3] =  2;

                    cellIDs_[tx-2 + (ty+2)*size_.x*3] =  2;
                }
            }

            if (cellIDs_[tx-3 + ty*size_.x*3] == 2) {        // LEFT
                cellIDs_[tx-1 + ty*size_.x*3] =  2;
                cellIDs_[tx-2 + ty*size_.x*3] =  2;
            }
        }

        if (y > 0) {
            if (cellIDs_[tx + (ty-3)*size_.x*3] == 2) {      // TOP
                cellIDs_[tx + (ty-1)*size_.x*3] =  2;
                cellIDs_[tx + (ty-2)*size_.x*3] =  2;
            }
        }

        if (y < size_.y-1) {
            if (cellIDs_[tx + (ty+3)*size_.x*3] == 2) {      // BOTTOM
                cellIDs_[tx + (ty+1)*size_.x*3] =  2;
                cellIDs_[tx + (ty+2)*size_.x*3] =  2;
            }
        }

// CORRECTING THE FINAL SHAPE OF THE SHADOWS
/*
        if (  isFilled(x, y, 2)
            ) return;

        if (  isFilled(x-1, y-1, 2)
           && isFilled( x , y-1, 2)
           && isFilled(x+1, y-1, 2)
           && isFilled(x+1,  y , 2)
           && isFilled(x+1, y+1, 2)
           && isFilled( x , y+1, 2)
           && isFilled(x-1, y+1, 2)
           && isFilled(x-1,  y , 2)
            ) return;
*/
        std::vector<char> neighbors;
        if (x > 0) {
            if (  y > 0
                ) neighbors.push_back(1);

            if (  y < size_.y-1
                ) neighbors.push_back(7);

            neighbors.push_back(8);
        }

        if (x < size_.x-1) {
            if (  y > 0
                ) neighbors.push_back(3);

            if (  y < size_.y-1
                ) neighbors.push_back(5);

            neighbors.push_back(4);
        }
        
        if (  y > 0
            ) neighbors.push_back(2);

        if (  y < size_.y-1
            ) neighbors.push_back(6);

        for (unsigned i=0; i<neighbors.size(); ++i) {
            switch (neighbors[i]) {    // here we switch between the central cell and the cells next to it
                case 0: tx = 3*( x ) + 1; ty = 3*( y ) + 1; break;              // CENTER
                case 1: tx = 3*(x-1) + 1; ty = 3*(y-1) + 1; break;              // TOP LEFT
                case 2: tx = 3*( x ) + 1; ty = 3*(y-1) + 1; break;              // TOP
                case 3: tx = 3*(x+1) + 1; ty = 3*(y-1) + 1; break;              // TOP RIGHT
                case 4: tx = 3*(x+1) + 1; ty = 3*( y ) + 1; break;              // RIGHT
                case 5: tx = 3*(x+1) + 1; ty = 3*(y+1) + 1; break;              // BOTTOM RIGHT
                case 6: tx = 3*( x ) + 1; ty = 3*(y+1) + 1; break;              // BOTTOM
                case 7: tx = 3*(x-1) + 1; ty = 3*(y+1) + 1; break;              // BOTTOM LEFT
                case 8: tx = 3*(x-1) + 1; ty = 3*( y ) + 1; break;              // LEFT
            }

            if (  cellIDs_[tx-1 + ( ty )*size_.x*3] == 2       // IF LEFT
               && cellIDs_[ tx  + (ty-1)*size_.x*3] == 2       // AND TOP ARE TRANSPARENT
                ) cellIDs_[tx-1 + (ty-1)*size_.x*3] =  2;      // THEN SET TOP LEFT TO TRANSPARENT

            if (  cellIDs_[tx-1 + ( ty )*size_.x*3] == 2       // IF LEFT
               && cellIDs_[ tx  + (ty+1)*size_.x*3] == 2       // AND BOTTOM ARE TRANSPARENT
                ) cellIDs_[tx-1 + (ty+1)*size_.x*3] =  2;      // THEN SET BOTTOM LEFT TO TRANSPARENT

            if (  cellIDs_[tx+1 + ( ty )*size_.x*3] == 2       // IF RIGHT
               && cellIDs_[ tx  + (ty-1)*size_.x*3] == 2       // AND TOP ARE TRANSPARENT
                ) cellIDs_[tx+1 + (ty-1)*size_.x*3] =  2;      // THEN SET TOP RIGHT TO TRANSPARENT

            if (  cellIDs_[tx+1 + ( ty )*size_.x*3] == 2       // IF RIGHT
               && cellIDs_[ tx  + (ty+1)*size_.x*3] == 2       // AND BOTTOM ARE TRANSPARENT
                ) cellIDs_[tx+1 + (ty+1)*size_.x*3] =  2;      // THEN SET BOTTOM RIGHT TO TRANSPARENT

            if (  cellIDs_[tx-1 + (ty-1)*size_.x*3] == 2       // IF TOP LEFT
               && cellIDs_[tx-1 + (ty+1)*size_.x*3] == 2       // AND BOTTOM LEFT ARE TRANSPARENT
                ) cellIDs_[tx-1 + ( ty )*size_.x*3] =  2;      // THEN SET LEFT TO TRANSPARENT

            if (  cellIDs_[tx-1 + (ty-1)*size_.x*3] == 2       // IF TOP LEFT
               && cellIDs_[tx+1 + (ty-1)*size_.x*3] == 2       // AND TOP RIGHT ARE TRANSPARENT
                ) cellIDs_[ tx  + (ty-1)*size_.x*3] =  2;      // THEN SET TOP TO TRANSPARENT

            if (  cellIDs_[tx+1 + (ty+1)*size_.x*3] == 2       // IF BOTTOM RIGHT
               && cellIDs_[tx+1 + (ty-1)*size_.x*3] == 2       // AND TOP RIGHT ARE TRANSPARENT
                ) cellIDs_[tx+1 + ( ty )*size_.x*3] =  2;      // THEN SET RIGHT TO TRANSPARENT

            if (  cellIDs_[tx+1 + (ty+1)*size_.x*3] == 2       // IF BOTTOM RIGHT
               && cellIDs_[tx-1 + (ty+1)*size_.x*3] == 2       // AND BOTTOM LEFT ARE TRANSPARENT
                ) cellIDs_[ tx  + (ty+1)*size_.x*3] =  2;      // THEN SET BOTTOM TO TRANSPARENT
        }
    }

    void ShadowMap::darken() {
        for (unsigned i=0; i<3*size_.x*size_.y; ++i) {
            cellIDs_[i] = 0;
        }
        for (unsigned x=0; x<size_.x; ++x) {
            for (unsigned y=0; y<size_.y; ++y) {
                if (  discovered_[x + y*size_.x]
                    ) fillCell(x, y, 1);
            }
        }
    }

    void ShadowMap::update() {
        for (unsigned x=0; x<3*size_.x; ++x) {
            for (unsigned y=0; y<3*size_.y; ++y) {
                switch (cellIDs_[x + y*3*size_.x]) {
                    case 0: shadowImage_.setPixel(x, y, sf::Color(0, 0, 0, 255)); break;
                    case 1: shadowImage_.setPixel(x, y, sf::Color(0, 0, 0, 200)); break;
                    case 2: shadowImage_.setPixel(x, y, sf::Color(0, 0, 0,   0)); break;
                }
            }
        }

        shadowTexture_.loadFromImage(shadowImage_);
    }

    std::ifstream& ShadowMap::operator<<(std::ifstream& file) {
        try {
            for (unsigned x=0; x<size_.x; ++x) {
                for (unsigned y=0; y<size_.y; ++y) {
                    readFile <bool> (file, discovered_[x + y*size_.x]);
                }
            }
        }
        catch (std::invalid_argument ex) {
            std::cerr << ex.what() << '\n';
        }

        return file;
    }

    std::ofstream& ShadowMap::operator>>(std::ofstream& file) {
        for (unsigned x=0; x<size_.x; ++x) {
            for (unsigned y=0; y<size_.y; ++y) {
                file << discovered_[x + y*size_.x] << ' ';
            }
            file << '\n';
        }

        return file;
    }

}
