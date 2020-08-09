#include "line.hpp"
#include <math.h>
#include <stdio.h>
#include <stdio.h>
#define PI 3.1415926536

Line::Line() {}

Line::Line(int nlines) {
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4 * nlines);
}
Line::~Line() {}

void Line::traceline(sf::Vector2f a, sf::Vector2f b, sf::Color color, float thick, int n) {
    angle = -atan2(b.y - a.y, b.x - a.x);
    if(angle < 0) angle += 2 * PI;
    if(angle > 2*PI) angle -= 2 * PI;
    sf::Vertex* line = &m_vertices[n * 4];
    line[0].position = sf::Vector2f(b.x + (thick / 2) * sin(angle), b.y + (thick / 2) * cos(angle));
    line[1].position = sf::Vector2f(a.x + (thick / 2) * sin(angle), a.y + (thick / 2) * cos(angle));
    line[2].position = sf::Vector2f(a.x - (thick / 2) * sin(angle), a.y - (thick / 2) * cos(angle));
    line[3].position = sf::Vector2f(b.x - (thick / 2) * sin(angle), b.y - (thick / 2) * cos(angle));
    line[0].color = color;
    line[1].color = color;
    line[2].color = color;
    line[3].color = color;
}

void Line::draw(sf::RenderTarget & target, sf:: RenderStates states) const {
    target.draw(m_vertices, states);
}