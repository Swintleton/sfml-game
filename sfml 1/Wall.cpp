#include "stdafx.h"
#include "Wall.h"

Wall::Wall(sf::Texture &texture, float posX, float posY, unsigned short _direction) :beforePlayer(false)
{
	direction = (directions)_direction;

	collisionRect.setTexture(nullptr);
	collisionRect.setPosition(posX, posY);

	wall.setTexture(texture);
	wall.setPosition(posX, posY);

	if (direction == UP || direction == DOWN) {
		collisionRect.setSize(sf::Vector2f{ 62.f, 40.f });
		collisionRect.setOrigin(31.f, 30.f);

		wall.setOrigin(31.f, 55.f);
	}
	else if (direction == RIGHT || direction == LEFT) {
		collisionRect.setSize(sf::Vector2f{ 20.f, 64.f });
		collisionRect.setOrigin(22.f, 40.f);

		wall.setOrigin(24.f, 72.f);
	}
	else {
		collisionRect.setSize(sf::Vector2f{ 30.f, 10.f });
		collisionRect.setOrigin(12.f, 20.f);
		collisionRect.rotate(-35);

		wall.setOrigin(44.f, 76.f);
	}
}

void Wall::draw(sf::RenderWindow &window) const {
	window.draw(wall);
	//window.draw(collisionRect);
}

sf::Sprite Wall::getSprite() const {
	return wall;
}