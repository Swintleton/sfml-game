#pragma once
#include <SFML\Graphics.hpp>

class Label
{
public:
	sf::RectangleShape rc;
	sf::Text text;
	bool visible;

	Label();
	Label(sf::Font &, float x, float y, float w, float h, std::string text);
	void draw(sf::RenderWindow &) const;
	void setFont(sf::Font &);
	void setPos(float x, float y);
	void setSize(float w, float h);
	void setText(std::string txt);
	void setTextPos(float x, float y);
};
