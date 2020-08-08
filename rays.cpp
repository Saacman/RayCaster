#include <math.h>
#include "rays.hpp"
#define PI 3.1415926536
#define HALF_PI PI/2
#define HALF_3PI 3*PI/2
Rays::Rays() {}
Rays::Rays(int nrays) : norays(nrays) {
    m_vertices.setPrimitiveType(sf::Lines);
    m_vertices.resize(nrays * 2);
}
Rays::~Rays() {}

float distance(float ax, float ay, float bx, float by) {
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void Rays::computeRays(sf::Vector2f position, float angle, const int* map) {
    float tileStepX, tileStepY, xstep, ystep;
    int mapx, mapy, mapp, depth;
    float rangle = angle;
    for(int i = 0; i < norays; i++) {
        depth = 0;
        // Horizontal lines
        float ncotan = -1 / tan(rangle);
        float disth = 100000000.f, distv = 100000000.f;
        if(rangle > PI) { // Looking up
            ystep = (((int)position.y >> 6) << 6) - 0.0001; // Remove the less significant bits to get a 64 multiple
            xstep = (position.y - ystep) * ncotan + position.x;
            tileStepY = -64;// Tile size
            tileStepX = -tileStepY * ncotan;
        }
        if(rangle < PI) { // Looking down
            ystep = (((int)position.y >> 6) << 6) + 64; 
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
            if(mapp > 0 && mapp < (8 * 8) && map[mapp] == 1) {
                disth = distance(position.x, position.y, xstep, ystep);
                depth = 8; // Hit the wall
            } else {
                xstep += tileStepX;
                ystep += tileStepY;
                depth++;
            }
            
        }
        float hxintercept = xstep, hyintercept = ystep;

        // Vertical Lines
        depth = 0;
        float ntan = -tan(rangle);
        if(rangle > HALF_PI && rangle < HALF_3PI) { // Looking left
            xstep = (((int)position.x >> 6) << 6) - 0.0001; // Remove the less significant bits to get a 64 multiple
            ystep = (position.x - xstep) * ntan + position.y;
            tileStepX = -64;// Tile size
            tileStepY = -tileStepX * ntan;
        }
        if(rangle < HALF_PI || rangle > HALF_3PI) { // Looking right
            xstep = (((int)position.x >> 6) << 6) + 64; 
            ystep = (position.x - xstep) * ntan + position.y;
            tileStepX = 64;
            tileStepY = -tileStepX * ntan;
        }
        if(rangle == 0 || rangle == PI) { // Looking up or down; probably won't happen.
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
            if(mapp > 0 && mapp < (8 * 8) && map[mapp] == 1) {
                distv = distance(position.x, position.y, xstep, ystep);
                depth = 8; // Hit the wall
            } else {
                xstep += tileStepX;
                ystep += tileStepY;
                depth++;
            }
            
        }
        float vxintercept = xstep, vyintercept = ystep;
        
        sf::Vertex* ray = &m_vertices[i * 2];
        ray[0].position = position;
        if(disth < distv) ray[1].position = sf::Vector2f(hxintercept, hyintercept);
        if(distv < disth) ray[1].position = sf::Vector2f(vxintercept, vyintercept);
        ray[0].color = sf::Color::Blue;
        ray[1].color = sf::Color::Blue;

    }
}

void Rays::draw(sf::RenderTarget & target, sf:: RenderStates states) const {
    target.draw(m_vertices, states);
}