#pragma once
#include <SFML\Graphics.hpp>

class Regenerator
{
public:
	unsigned int id;
	float active;
	sf::RectangleShape rc;
	sf::Uint8 type;

	Regenerator(unsigned int id, float x, float y, float w, float h, bool active, sf::Uint8 type);
	void draw(sf::RenderWindow &) const;
};