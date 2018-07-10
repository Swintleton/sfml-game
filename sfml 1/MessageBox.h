#pragma once
#include <SFML/Graphics.hpp>
#include "MessageList.h"

class MessageBox
{
public:
	sf::RectangleShape rc;
	sf::RectangleShape collisionRect;
	bool selected;
	bool visible;
	char sendMsg[255];

	MessageBox();
	void draw(sf::RenderWindow &) const;
	void setPosition(float, float);
	void setFont(sf::Font &);
	bool update(sf::RenderWindow &, sf::Event &);
private:
	sf::String input;
	sf::Text text;
	sf::Color selectedColor;
	sf::Color normalColor;
	bool send;
};
