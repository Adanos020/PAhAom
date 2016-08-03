/**
 * @file src/program/game/fov/FOV.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include <cmath>
#include <iostream>

#include "FOV.hpp"

namespace rr {
    
    void FOV::compute(ShadowMap* shadows, int tiles[], sf::Vector2u origin, int range) {
        shadows->setLit((sf::Vector2i) origin);
        for (unsigned octant = 0; octant < 8; octant++) {
            compute(shadows, tiles, octant, origin, 2*range, 1, Slope(1, 1), Slope(0, 1));
        }
    }

    void FOV::compute(ShadowMap* shadows, int tiles[], unsigned octant, sf::Vector2u origin, int range, unsigned x, Slope top, Slope bottom) {
        for (; x <= (unsigned)range; x++) {
            unsigned topY;
            if (  top.x_ == 1
                ) topY = x;
            else {
                topY = ((x*2-1)*top.y_+top.x_) / (top.x_*2);
                if (  blocksLight(tiles, x, topY, octant, origin)
                   && top >= Slope(topY*2+1, x*2)
                   && !blocksLight(tiles, x, topY+1, octant, origin)
                    ) topY++;
                else {
                    unsigned ax = x*2;
                    if (  blocksLight(tiles, x+1, topY+1, octant, origin)
                        ) ax++;
                    if (  top > Slope(topY*2+1, ax)
                        ) topY++;
                }
            }

            unsigned bottomY;
            if (  bottom.y_ == 0
                ) bottomY = 0;
            else {
                bottomY = ((x*2-1)*bottom.y_+bottom.x_)/(bottom.x_*2);
                if (  bottom >= Slope(bottomY*2+1, x*2)
                   && blocksLight(tiles, x, bottomY, octant, origin) 
                   &&!blocksLight(tiles, x, bottomY+1, octant, origin)
                    ) bottomY++;
            }

            int wasOpaque = -1;
            for (unsigned y = topY; (int)y >= (int)bottomY; y--) {
                if (range < 0 || getDistance((int)x, (int)y) <= range) {
                    bool isOpaque = blocksLight(tiles, x, y, octant, origin);
                    
                    if (  isOpaque 
                       || (  (  y != topY
                             || top    > Slope(y*4-1, x*4+1)
                              )
                          && (  y != bottomY
                             || bottom < Slope(y*4+1, x*4-1)
                              )
                           )
                        ) setVisible(shadows, x, y, octant, origin);

                    if ((int)x != range) {
                        if (isOpaque) {
                            if (wasOpaque == 0) {
                                unsigned nx = x*2, ny = y*2+1;
                                if (  blocksLight(tiles, x, y+1, octant, origin)
                                    ) nx--;
                                if (top > Slope(ny, nx)) {
                                    if (y == bottomY) {
                                        bottom = Slope(ny, nx);
                                        break;
                                    }
                                    else compute(shadows, tiles, octant, origin, range, x+1, top, Slope(ny, nx));
                                }
                                else if (  y == bottomY
                                         ) return;
                            }
                            wasOpaque = 1;
                        }
                        else {
                            if (wasOpaque > 0) {
                                unsigned nx = x*2, ny = y*2+1;

                                if (  blocksLight(tiles, x+1, y+1, octant, origin)
                                    ) nx++;
                                if (  bottom >= Slope(ny, nx)
                                    ) return;
                                top = Slope(ny, nx);
                            }
                            wasOpaque = 0;
                        }
                    }
                }
            }
            if (  wasOpaque != 0
                ) break;
        }
    }

    bool FOV::blocksLight(int tiles[], unsigned x, unsigned y, unsigned octant, sf::Vector2u origin) {
        unsigned nx = origin.x, ny = origin.y;
        switch (octant) {
            case 0: nx += x; ny -= y; break;
            case 1: nx += y; ny -= x; break;
            case 2: nx -= y; ny -= x; break;
            case 3: nx -= x; ny -= y; break;
            case 4: nx -= x; ny += y; break;
            case 5: nx -= y; ny += x; break;
            case 6: nx += y; ny += x; break;
            case 7: nx += x; ny += y; break;
        }
        return ((nx < 77 && ny < 43) && (tiles[nx+ny*77] == 1 || tiles[nx+ny*77] == 4));
    }

    void FOV::setVisible(ShadowMap* shadows, unsigned x, unsigned y, unsigned octant, sf::Vector2u origin) {
        int nx = origin.x, ny = origin.y;
        switch (octant) {
            case 0: nx += x; ny -= y; break;
            case 1: nx += y; ny -= x; break;
            case 2: nx -= y; ny -= x; break;
            case 3: nx -= x; ny -= y; break;
            case 4: nx -= x; ny += y; break;
            case 5: nx -= y; ny += x; break;
            case 6: nx += y; ny += x; break;
            case 7: nx += x; ny += y; break;
        }
        shadows->setLit(sf::Vector2i(nx, ny));
    }

    int FOV::getDistance(int x, int y) {
        if (  x == 0
            ) return y;
        if (  y == 0
            ) return x;

        return (int)sqrt(x*x + y*y);
    }

}
