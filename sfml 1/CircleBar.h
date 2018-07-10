#pragma once
#include <sfml/Graphics.hpp>

class CircleBar
{
public:
	sf::CircleShape collisionCircle;
	sf::Text text;

	CircleBar(float, float);
	void draw(sf::RenderWindow &) const;
	bool hovered(sf::RenderWindow &);
	void setFont(sf::Font &);
	void setPosition(float, float);
	void setPosition(sf::Vector2f &);
	void setRadius(float);
	void setText(float);
	void setText(std::string);
	void setTexture(sf::Texture &);
	void setBorderTexture(sf::Texture &border);
	void setEffectTexture(sf::Texture &effect);
	void setSize(float);
	void setValue(float);
private:
	sf::CircleShape border;
	sf::CircleShape effect;
};

