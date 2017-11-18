#pragma once
#include <SFML\Graphics.hpp>

class Wall
{
public:
	Wall(sf::Texture,float,float);
	void draw(sf::RenderWindow &);
	~Wall();

	sf::RectangleShape wal;		//ONLY FOR COLLISION
private:
	sf::Sprite wall;
	sf::Texture texture;
};

