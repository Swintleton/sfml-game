#include "stdafx.h"
#include "Wall.h"

Wall::Wall(unsigned int id, sf::Texture &texture, float x, float y, sf::Uint8 _direction)
	: id(id), direction(_direction)
{
	collisionRect.setPosition(x, y);

	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	if (direction == 1 || direction == 4) {
		collisionRect.setSize(sf::Vector2f{ 62.f, 40.f });
		collisionRect.setOrigin(31.f, 30.f);

		sprite.setOrigin(31.f, 55.f);
	}
	else if (direction == 0 || direction == 7) {
		collisionRect.setSize(sf::Vector2f{ 20.f, 64.f });
		collisionRect.setOrigin(22.f, 40.f);

		sprite.setOrigin(24.f, 72.f);
	}
	else {
		collisionRect.setSize(sf::Vector2f{ 30.f, 10.f });
		collisionRect.setOrigin(12.f, 20.f);
		collisionRect.rotate(-35);

		sprite.setOrigin(44.f, 76.f);
	}
}

void Wall::draw(sf::RenderWindow &window) const {
	window.draw(sprite);
	//window.draw(collisionRect);
}