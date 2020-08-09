#include <math.h>
#include "rays.hpp"
#define PI 3.1415926536
#define RADIAN PI / 180
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
    float tileStepX, tileStepY, VXintercept = position.x, VYintercept, HXintercept, HYintercept;
    int mapx, mapy, mapp, depth;
    float rangle = angle - RADIAN * (norays/2);
    if(rangle < 0) rangle += 2 * PI;
    if(rangle > 2*PI) rangle -= 2 * PI;
    for(int i = 0; i < norays; i++) {
        depth = 0;
        // Horizontal lines
        float ncotan = -1 / tan(rangle);
        float disth = 1000000000.f, distv = 1000000000.f;
        if(rangle > PI) { // Looking up
            HYintercept = (((int)position.y >> 6) << 6) - 0.0001; // Remove the less significant bits to get a 64 multiple
            HXintercept = (position.y - HYintercept) * ncotan + position.x;
            tileStepY = -64;// Tile size
            tileStepX = -tileStepY * ncotan;
        }
        if(rangle < PI) { // Looking down
            HYintercept = (((int)position.y >> 6) << 6) + 64; 
            HXintercept = (position.y - HYintercept) * ncotan + position.x;
            tileStepY = 64;// Tile size
            tileStepX = -tileStepY * ncotan;
        }
        if(rangle == 0 || rangle == PI) { // Looking left or right; probably won't happen.
            HXintercept = position.x;
            HYintercept = position.y;
            depth = 8;
        }

        while(depth < 8) {
            // Find the position in the map
            mapx = (int)HXintercept >> 6;
            mapy = (int)HYintercept >> 6;
            // Find the position in the array
            mapp = mapy * 8 + mapx; // Magic number
            if(mapp > 0 && mapp < (8 * 8) && map[mapp] == 1) {
                disth = distance(position.x, position.y, HXintercept, HYintercept);
                depth = 8; // Hit the wall
            } else {
                HXintercept += tileStepX;
                HYintercept += tileStepY;
                depth++;
            }
            
        }
        
        // Vertical Lines
        depth = 0;
        float ntan = -tan(rangle);
        if(rangle > HALF_PI && rangle < HALF_3PI) { // Looking left
            VXintercept = (((int)position.x >> 6) << 6) - 0.0001; // Remove the less significant bits to get a 64 multiple
            VYintercept = (position.x - VXintercept) * ntan + position.y;
            tileStepX = -64;// Tile size
            tileStepY = -tileStepX * ntan;
        }
        if(rangle < HALF_PI || rangle > HALF_3PI) { // Looking right
            VXintercept = (((int)position.x >> 6) << 6) + 64; 
            VYintercept = (position.x - VXintercept) * ntan + position.y;
            tileStepX = 64;
            tileStepY = -tileStepX * ntan;
        }
        if(rangle == HALF_PI || rangle == HALF_3PI) { // Looking up or down; probably won't happen.
            VXintercept = position.x;
            VYintercept = position.y;
            depth = 8;
        }

        while(depth < 8) {
            // Find the position in the map
            mapx = (int)VXintercept >> 6;
            mapy = (int)VYintercept >> 6;
            // Find the position in the array
            mapp = mapy * 8 + mapx; // Magic number
            if(mapp > 0 && mapp < (8 * 8) && map[mapp]) {
                distv = distance(position.x, position.y, VXintercept, VYintercept);
                depth = 8; // Hit the wall
            } else {
                VXintercept += tileStepX;
                VYintercept += tileStepY;
                depth++;
            }
        }
        
        sf::Vertex* ray = &m_vertices[i * 2];
        ray[0].position = position;
        if(disth < distv) ray[1].position = sf::Vector2f(HXintercept, HYintercept);
        if(distv < disth) ray[1].position = sf::Vector2f(VXintercept, VYintercept);
        ray[0].color = sf::Color::Red;
        ray[1].color = sf::Color::Red;
        rangle += RADIAN;
        if(rangle < 0) rangle += 2 * PI;
        if(rangle > 2*PI) rangle -= 2 * PI;
    }
}

void Rays::draw(sf::RenderTarget & target, sf:: RenderStates states) const {
    target.draw(m_vertices, states);
}