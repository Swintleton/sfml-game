#include "stdafx.h"
#include "MenuItem.h"

MenuItem::MenuItem(sf::Vector2f pos, sf::Vector2f size, sf::Font &font, char *buttonText)
{
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString(buttonText);
	text.setPosition(pos);

	rc.setFillColor(sf::Color::Black);
	rc.setOrigin(0, -10);
	rc.setPosition(pos);
	rc.setSize(size);
}

void MenuItem::setPosition(float x, float y)
{
	text.setPosition(x, y);
	rc.setPosition(x, y);
}

void MenuItem::draw(sf::RenderWindow &window) const {
	window.draw(rc);
	window.draw(text);
}

void MenuItem::setColor(const sf::Color color) {
	text.setFillColor(color);
}