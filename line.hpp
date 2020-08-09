#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>

class Line : public sf::Drawable
{
public:
	Line();
	Line(int nlines);
	~Line();
	void traceline(sf::Vector2f a, sf::Vector2f b, sf::Color color = sf::Color::Blue, float thick = 2, int n = 1);
private:
	virtual void draw(sf::RenderTarget & target, sf:: RenderStates states) const;
	sf::VertexArray m_vertices;
	float thickness;
	sf::Vector2f pointA;
	sf::Vector2f pointB;
	float angle;
};



#endif