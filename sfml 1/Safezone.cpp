#include "stdafx.h"
#include "Safezone.h"

Safezone::Safezone(unsigned int id, float x, float y, float w, float h, bool active) : id(id), active(active)
{
	rc.setPosition(x, y);
	rc.setSize(sf::Vector2f(w, h));
	rc.setOrigin(x / 2, y / 2);
	rc.setFillColor(sf::Color(0, 0, 255, 80));
}

void Safezone::draw(sf::RenderWindow &window) const {
	window.draw(rc);
}