#include <math.h>
#include "rays.hpp"
#define PI 3.1415926536

Rays::Rays() {}

Rays::~Rays() {}

void Rays::computeRays(sf::Vector2f position, float angle, const int* map, int nrays) {
    m_vertices.setPrimitiveType(sf::Lines);
    m_vertices.resize(nrays * 2);
    float tileStepX, tileStepY, xstep, ystep;//, xintercept, yintercept;
    int mapx, mapy, mapp, depth;
    float rangle = angle;
    for(int i = 0; i < nrays; i++) {
        depth = 0;
        // Horizontal lines
        float ncotan = -1.0 / tan(rangle);
        if(rangle > PI) { // Looking up
            ystep = ((int)position.y >> 6) << 6; // Remove the less significant bits to get a 64 multiple
            xstep = (position.y - ystep) * ncotan + position.x;
            tileStepY = -64;// Tile size
            tileStepX = -tileStepY * ncotan;
        }
        if(rangle < PI) { // Looking down
            ystep = (((int)position.y >> 6) << 6) + 64.0; 
            xstep = (position.y - ystep) * ncotan + position.x;
            tileStepY = 64;// Tile size
            tileStepX = -tileStepY * ncotan;
        }
        if(rangle == 0 || rangle == PI) { // Looking left or right; probably won't happen.
            xstep = position.x;
            ystep = position.y;
            depth = 8;
        }

        while(depth < 8) {
            // Find the position in the map
            mapx = (int)xstep >> 6;
            mapy = (int)ystep >> 6;
            // Find the position in the array
            mapp = mapy * 8 + mapx; // Magic number
            if(mapp < 8 * 8 && map[mapp] == 1) {
                depth = 8; // Hit the wall
            } else {
                xstep += tileStepX;
                ystep += tileStepY;
                depth++;
            }
            
        }
        sf::Vertex* ray = &m_vertices[i * 2];
        ray[0].position = position;
        ray[1].position = sf::Vector2f(xstep, ystep);
        ray[0].color = sf::Color::Red;
        ray[1].color = sf::Color::Red;

    }
}

void Rays::draw(sf::RenderTarget & target, sf:: RenderStates states) const {
    target.draw(m_vertices, states);
}