#include "stdafx.h"
#include "Wall.h"

Wall::Wall(sf::Texture _texture, float posX, float posY,unsigned short _direction):texture(_texture)
{
	direction = (directions)_direction;

	collisionRect.setTexture(nullptr);
	collisionRect.setPosition(posX, posY);

	wall.setTexture(texture);
	wall.setPosition(posX, posY);

	if(direction == UP || direction == DOWN) {
		collisionRect.setSize(sf::Vector2f{ 35, 30 });
		collisionRect.setOrigin(18, 25);

		wall.setOrigin(31, 55);
	}
	else if(direction == RIGHT || direction == LEFT) {
		collisionRect.setSize(sf::Vector2f{ 1.f, 35 });
		collisionRect.setOrigin(12, 15);

		wall.setOrigin(24, 72);
	}
	else {
		collisionRect.setSize(sf::Vector2f{ 30, 10 });
		collisionRect.setOrigin(12, 20);
		collisionRect.rotate(-35);

		wall.setOrigin(44, 76);
	}
}

void Wall::draw(sf::RenderWindow &window)
{
	window.draw(wall);
	window.draw(collisionRect);
}

sf::Sprite Wall::getSprite() {
	return wall;
}

Wall::~Wall()
{
}
