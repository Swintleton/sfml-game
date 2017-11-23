#pragma once
#include <SFML\Graphics.hpp>

class Wall
{
public:
	Wall(sf::Texture, float, float, unsigned short);
	void draw(sf::RenderWindow &) const;

	sf::RectangleShape collisionRect;		//ONLY FOR COLLISION
	sf::Sprite getSprite() const;

	bool beforePlayer;

	enum directions { RIGHT, UP, UP_RIGHT, UP_LEFT, DOWN, DOWN_RIGHT, DOWN_LEFT, LEFT };
	directions direction;

	~Wall(void);
private:
	sf::Sprite wall;
	sf::Texture texture;
};
