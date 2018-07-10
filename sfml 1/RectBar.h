#pragma once
#include <SFML/Graphics.hpp>

class RectBar
{
public:
	sf::RectangleShape collisionRect;
	sf::Text text;

	RectBar(float, float);
	void draw(sf::RenderWindow &) const;
	void setFont(sf::Font &);
	void setPosition(float, float);
	void setSize(float, float);
	void setText(float);
	void setText(std::string);
	void setTexture(sf::Texture &);
	void setBorderTexture(sf::Texture &border);
	void setEffectTexture(sf::Texture &effect);
	void setValue(float);
private:
	sf::RectangleShape border;
};

