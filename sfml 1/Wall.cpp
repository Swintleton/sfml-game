#include "stdafx.h"
#include "Wall.h"

Wall::Wall(sf::Texture _texture, float posX, float posY,unsigned short _direction):texture(_texture),beforePlayer(0)
{
	direction = (directions)_direction;

	collisionRect.setTexture(nullptr);
	collisionRect.setPosition(posX, posY);

	wall.setTexture(texture);
	wall.setPosition(posX, posY);

	if(direction == UP || direction == DOWN) {
		collisionRect.setSize(sf::Vector2f{ 62, 40 });
		collisionRect.setOrigin(31, 30);

		wall.setOrigin(31, 55);
	}
	else if(direction == RIGHT || direction == LEFT) {
		collisionRect.setSize(sf::Vector2f{ 20.f, 62 });
		collisionRect.setOrigin(22, 40);

		wall.setOrigin(24, 72);
	}
	else {
		collisionRect.setSize(sf::Vector2f{ 30, 10 });
		collisionRect.setOrigin(12, 20);
		collisionRect.rotate(-35);

		wall.setOrigin(44, 76);
	}
}

void Wall::draw(sf::RenderWindow &window) const
{
	window.draw(wall);
	//window.draw(collisionRect);
}

sf::Sprite Wall::getSprite() const{
	return wall;
}

Wall::~Wall(void)
{
}
