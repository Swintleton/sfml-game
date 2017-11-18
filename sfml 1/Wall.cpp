#include "stdafx.h"
#include "Wall.h"

Wall::Wall(sf::Texture _texture, float posX, float posY):texture(_texture)
{
	wal.setTexture(nullptr);
	wal.setSize(sf::Vector2f { 10, 10 });
	wal.setPosition(posX, posY);
	wal.setOrigin(5,30);

	wall.setTexture(texture);
	wall.setOrigin(31,55);
	wall.setPosition(posX, posY);
}

void Wall::draw(sf::RenderWindow &window)
{
	window.draw(wall);
	window.draw(wal);
}

Wall::~Wall()
{
}
