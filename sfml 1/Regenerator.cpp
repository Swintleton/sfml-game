#include "stdafx.h"
#include "Regenerator.h"

Regenerator::Regenerator(unsigned int id, float x, float y, float w, float h, bool active, sf::Uint8 type)
	: id(id), active(active), type(type)
{
	rc.setPosition(x, y);
	rc.setSize(sf::Vector2f(w, h));
	rc.setOrigin(x / 2, y / 2);
	if (type == 0)
		rc.setFillColor(sf::Color(0, 255, 0, 150));
	else if (type == 1)
		rc.setFillColor(sf::Color(0, 0, 255, 150));
	else if (type == 2)
		rc.setFillColor(sf::Color(128, 0, 128, 150));
}

void Regenerator::draw(sf::RenderWindow &window) const {
	window.draw(rc);
}