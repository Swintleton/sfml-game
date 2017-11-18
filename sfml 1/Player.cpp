#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Texture Texture, float posX,float posY):
	stopped_Texture(Texture), textureWidth(96), textureHeight(96),animation(96,96,7,0.07f)
{
	player.setOrigin(textureWidth/2, textureHeight/2);
	player.setPosition(posX, posY);

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
	sf::Vector2f movement(0.0f, 0.0f);
	moving = false;
//----------------------DECIDE WALKING DIRECTION-----------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= speed * deltaTime;
		direction = directions::UP;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += speed * deltaTime;
		direction = directions::DOWN;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= speed * deltaTime;
		direction = directions::LEFT;
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += speed * deltaTime;
		direction = directions::RIGHT;
		moving = true;
	}
	//IN CASE OF DIAGONAL MOVING, IT'S SHOULD SLOW DOWN
	if(movement.y != 0.f && movement.x != 0.f)
		movement /= std::sqrt(2.f);

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

		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}
		*/
	}
//---------------------------------------------------------------------
//----------------------ANIMATION & COLLISION & MOVE-------------------
	if (moving) {
		animation.update(direction, walking_Texture, player, deltaTime);

		player.move(movement);
		
		for (sf::RectangleShape *other : collisionList) {
			if (player.getGlobalBounds().intersects(other->getGlobalBounds())) {
				if (direction == UP) {
					movement.y += 2*speed * deltaTime;
				}
				else if (direction == DOWN) {
					movement.y -= 2*speed * deltaTime;
				}
				else if (direction == LEFT) {
					movement.x += 2*speed * deltaTime;
				}
				else if (direction == RIGHT) {
					movement.x -=2* speed * deltaTime;
				}
				else if (direction == UP_RIGHT) {
					movement.y += std::sqrt(2.f) * speed * deltaTime;
					movement.x -= std::sqrt(2.f) * speed * deltaTime;
				}
				else if (direction == UP_LEFT) {
					movement.y += std::sqrt(2.f) * speed * deltaTime;
					movement.x += std::sqrt(2.f) * speed * deltaTime;
				}
				else if (direction == DOWN_RIGHT) {
					movement.y -= std::sqrt(2.f) * speed * deltaTime;
					movement.x -= std::sqrt(2.f) * speed * deltaTime;
				}
				else if (direction == DOWN_LEFT) {
					movement.y -= std::sqrt(2.f) * speed * deltaTime;
					movement.x += std::sqrt(2.f) * speed * deltaTime;
				}
				player.move(movement);
			}
		}
	}
//---------------------------------------------------------------------
}

void const Player::draw(sf::RenderWindow &window)
{
	window.draw(player);
}
sf::Vector2f Player::getPositon()
{
	return player.getPosition();
}

Player::~Player(void)
{
}