/**
 * @file src/program/game/fov/fov_FOV.cpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#include "fov.hpp"

#include <cmath>

namespace rr {

    FOV::FOV(std::vector<std::vector<Mask*>>* masks, std::vector<std::vector<int>>* tiles)
    : masks_ (masks),
      tiles_ (tiles) {}

    void FOV::compute(sf::Vector2u origin, int range) {
        masks_->at(origin.x)[origin.y]->see(true);
        for (unsigned octant = 0; octant < 8; octant++) {
            compute(octant, origin, 2*range, 1, Slope(1, 1), Slope(0, 1));
        }
    }

    void FOV::compute(unsigned octant, sf::Vector2u origin, int range, unsigned x, Slope top, Slope bottom) {
        for (; x <= (unsigned)range; x++) {
            unsigned topY;
            if (top.x_ == 1)
                topY = x;
            else {
                topY = ((x*2-1)*top.y_+top.x_)/(top.x_*2);
                if (blocksLight(x, topY, octant, origin) && top >= Slope(topY*2+1, x*2) && !blocksLight(x, topY+1, octant, origin))
                    topY++;
                else {
                    unsigned ax = x*2;
                    if (blocksLight(x+1, topY+1, octant, origin))
                        ax++;
                    if (top > Slope(topY*2+1, ax))
                        topY++;
                }
            }

            unsigned bottomY;
            if (bottom.y_ == 0)
                bottomY = 0;
            else {
                bottomY = ((x*2-1)*bottom.y_+bottom.x_)/(bottom.x_*2);
                if (bottom >= Slope(bottomY*2+1, x*2) && blocksLight(x, bottomY, octant, origin) && !blocksLight(x, bottomY+1, octant, origin))
                    bottomY++;
            }

            int wasOpaque = -1;
            for (unsigned y = topY; (int)y >= (int)bottomY; y--) {
                if (range < 0 || getDistance((int)x, (int)y) <= range) {
                    bool isOpaque  = blocksLight(x, y, octant, origin);
                    bool isVisible = isOpaque || ((y != topY || top > Slope(y*4-1, x*4+1)) && (y != bottomY || bottom < Slope(y*4+1, x*4-1)));
                    if (isVisible)
                        setVisible(x, y, octant, origin);

                    if ((int)x != range) {
                        if (isOpaque) {
                            if (wasOpaque == 0) {
                                unsigned nx = x*2, ny = y*2+1;
                                if (blocksLight(x, y+1, octant, origin))
                                    nx--;
                                if (top > Slope(ny, nx)) {
                                    if (y == bottomY) {
                                        bottom = Slope(ny, nx);
                                        break;
                                    }
                                    else
                                        compute(octant, origin, range, x+1, top, Slope(ny, nx));
                                }
                                else if (y == bottomY)
                                    return;
                            }
                            wasOpaque = 1;
                        }
                        else {
                            if (wasOpaque > 0) {
                                unsigned nx = x*2, ny = y*2+1;

                                if (blocksLight(x+1, y+1, octant, origin))
                                    nx++;
                                if (bottom >= Slope(ny, nx))
                                    return;
                                top = Slope(ny, nx);
                            }
                            wasOpaque = 0;
                        }
                    }
                }
            }
            if (wasOpaque != 0)
                break;
        }
    }

    bool FOV::blocksLight(unsigned x, unsigned y, unsigned octant, sf::Vector2u origin) {
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
        return (nx < tiles_->size() && ny < tiles_[0].size()) && (tiles_->at(nx)[ny] == 1 || tiles_->at(nx)[ny] == 4);
    }

    void FOV::setVisible(unsigned x, unsigned y, unsigned octant, sf::Vector2u origin) {
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
        masks_->at(nx)[ny]->see(true);
    }

    int FOV::getDistance(int x, int y) {
        if (x == 0) return y;
        if (y == 0) return x;
        return (int)sqrt(x*x + y*y);
    }

}
