#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
	unsigned int id;
	sf::RectangleShape collisionRect;

	//DIRECTIONS:
	//	0	-	RIGHT
	//	1	-	UP
	//	2	-	UP RIGHT
	//	3	-	UP LEFT
	//	4	-	DOWN
	//	5	-	DOWN RIGHT
	//	6	-	DOWN LEFT
	//	7	-	LEFT
	sf::Uint8 direction;
	sf::Sprite sprite;

	Wall(unsigned int id, sf::Texture &, float x, float y, sf::Uint8 direction);
	void draw(sf::RenderWindow &) const;
};
