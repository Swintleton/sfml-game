#pragma once
#include <SFML\Graphics.hpp>

class Wall
{
public:
	Wall(sf::Texture,float,float);
	void draw(sf::RenderWindow &);
	~Wall();

	sf::RectangleShape wal;		//ONLY FOR COLLISION
	sf::Sprite wall;
private:
	
	sf::Texture texture;
};
