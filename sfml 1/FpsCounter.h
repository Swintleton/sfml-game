#pragma once
#include <SFML\Graphics.hpp>

class FpsCounter
{
public:
	sf::Text text;
	unsigned int frameCount;
	float deltaTime;
	bool visible;

	FpsCounter();
	void draw(sf::RenderWindow &) const;
	float getFPS(void);
	void setFont(sf::Font &);
	void setPosition(float, float);
	void setPosition(sf::Vector2f);
	void update(float);
};

