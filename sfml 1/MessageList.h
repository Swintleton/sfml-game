#pragma once
#include <SFML/Graphics.hpp>
#include "ScrollBar.h"

class MessageList
{
public:
	sf::RectangleShape rc;
	sf::RectangleShape collisionRect;
	ScrollBar scrollBar;
	std::vector<std::string> messages;
	bool selected;
	bool visible;
	unsigned int visibleFrom;
	unsigned char visibleUntil;

	MessageList();
	void addMessage(char *);
	void draw(sf::RenderWindow &) const;
	void setPosition(float, float);
	void setFont(sf::Font &);
	void update(sf::RenderWindow &, sf::Uint32 pressedKey);
private:
	sf::Text text;
	sf::Color selectedColor;
	sf::Color normalColor;
};
