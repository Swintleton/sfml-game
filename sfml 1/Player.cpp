#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Texture Texture, float posX,float posY):
	stopped_Texture(Texture), textureWidth(96), textureHeight(96),animation(96,96,7,0.07f)
{
	player.setOrigin(textureWidth/2, textureHeight/2);
	player.setPosition(posX, posY);

	collisionRect.setTexture(nullptr);
	collisionRect.setPosition(posX, posY);
	collisionRect.setSize(sf::Vector2f{ 26, 44 });
	collisionRect.setOrigin(13, 22);

	moving = false;

	player.setTexture(stopped_Texture);
	player.setTextureRect(sf::IntRect(0, 0, 96, 96));
	
	direction = directions::RIGHT;
	speed = 100.0f;
}
void Player::addWalkingTexutre(sf::Texture Texture) {
	walking_Texture = Texture;
}

void const Player::update(float deltaTime, std::list<sf::RectangleShape *> &collisionList)
{
	sf::Vector2f movement(0.f, 0.f);
	moving = false;
//----------------------DECIDE WALKING DIRECTION-----------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= speed * deltaTime;
		direction = directions::UP;
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += speed * deltaTime;
		direction = directions::DOWN;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= speed * deltaTime;
		direction = directions::LEFT;
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += speed * deltaTime;
		direction = directions::RIGHT;
		moving = true;
	}
	//IN CASE OF DIAGONAL MOVING, IT'S SHOULD SLOW DOWN
	if(movement.y != 0.f && movement.x != 0.f)
		movement /= SQRT_2;

	if (movement.y < 0.f && movement.x > 0.f)
	{
		direction = directions::UP_RIGHT;
	}
	else if (movement.y < 0.f && movement.x < 0.f)
	{
		direction = directions::UP_LEFT;
	}
	else if (movement.y > 0.f && movement.x > 0.f)
	{
		direction = directions::DOWN_RIGHT;
	}
	else if (movement.y > 0.f && movement.x < 0.f)
	{
		direction = directions::DOWN_LEFT;
	}
//---------------------------------------------------------------------
//----------------------SET STOPPED TEXTURE----------------------------
	if (!moving) {
		player.setTexture(stopped_Texture);
		player.setTextureRect(sf::IntRect(textureWidth * direction, 0, textureWidth, textureHeight));
	}
//---------------------------------------------------------------------
//----------------------ANIMATION & COLLISION & MOVE-------------------
	if (moving) {
		animation.update(direction, walking_Texture, player, deltaTime);

		collisionRect.move(movement);
		player.move(movement);

		for (sf::RectangleShape *other : collisionList) {
			if (collisionRect.getGlobalBounds().intersects(other->getGlobalBounds())) {
				if (direction == UP) {
					movement.y += 2*speed * deltaTime;
				}
				else if (direction == DOWN) {
					movement.y -= 2*speed * deltaTime;
				}
				if (direction == LEFT) {
					movement.x += 2*speed * deltaTime;
				}
				else if (direction == RIGHT) {
					movement.x -=2* speed * deltaTime;
				}
				if (direction == UP_RIGHT) {
					movement.y += SQRT_2 * speed * deltaTime;
					movement.x -= SQRT_2 * speed * deltaTime;
				}
				else if (direction == UP_LEFT) {
					movement.y += SQRT_2 * speed * deltaTime;
					movement.x += SQRT_2 * speed * deltaTime;
				}
				else if (direction == DOWN_RIGHT) {
					movement.y -= SQRT_2 * speed * deltaTime;
					movement.x -= SQRT_2 * speed * deltaTime;
				}
				else if (direction == DOWN_LEFT) {
					movement.y -= SQRT_2 * speed * deltaTime;
					movement.x += SQRT_2 * speed * deltaTime;
				}
				collisionRect.move(movement);
				player.move(movement);
			}
		}
	}
//---------------------------------------------------------------------
}

void const Player::draw(sf::RenderWindow &window) const
{
	//window.draw(collisionRect);
	window.draw(player);
}

Player::~Player(void)
{
}