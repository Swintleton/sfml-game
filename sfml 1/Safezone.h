#pragma once
#include <SFML\Graphics.hpp>

class Safezone
{
public:
	unsigned int id;
	float active;
	sf::RectangleShape rc;

	Safezone(unsigned int id, float x, float y, float w, float h, bool active);
	void draw(sf::RenderWindow &) const;
};