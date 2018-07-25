#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y)
:direction(4),speed(100),dead(false),doAttack(false),doMove(false),doBeenHit(false),doDie(false),animation(96, 96, 7, 0.07f),running(false),maxHealth(10),health(10),maxMana(10),mana(10),textureWidth(96),textureHeight(96),hitPicture(0),beenHitPicture(0),diePicture(0),healthBar(x-350,y+200),manaBar(x+260,y+200)
{
	sprite.setOrigin(textureWidth / 2.f, textureHeight / 2.f);
	sprite.setPosition(x, y);
	sprite.setTextureRect(sf::IntRect(0, 0, textureWidth, textureHeight));

	collisionRect.setPosition(x, y);
	collisionRect.setSize(sf::Vector2f{ 26, 44 });
	collisionRect.setOrigin(13, 22);

	sound_Move.setVolume(30);
	sound_Move.setLoop(true);
	sound_Hit.setVolume(30);

	attackSpeed = 0.63f;
}

bool Player::move(float deltaTime, std::vector<Wall> &walls)
{
	sf::Vector2f movement(0.f, 0.f);
//-------------------------DECIDE WALKING DIRECTION--------------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= speed * deltaTime;
		direction = 1;
		doMove = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += speed * deltaTime;
		direction = 4;
		doMove = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= speed * deltaTime;
		direction = 7;
		doMove = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += speed * deltaTime;
		direction = 0;
		doMove = true;
	}
	//IN CASE OF DIAGONAL MOVING, IT'S SHOULD SLOW DOWN
	if(movement.y != 0.f && movement.x != 0.f)
		movement /= SQRT_2;

	if (movement.y < 0.f && movement.x > 0.f)
	{
		direction = 2;
	}
	else if (movement.y < 0.f && movement.x < 0.f)
	{
		direction = 3;
	}
	else if (movement.y > 0.f && movement.x > 0.f)
	{
		direction = 5;
	}
	else if (movement.y > 0.f && movement.x < 0.f)
	{
		direction = 6;
	}
//---------------------------------------------------------------------------
//------------------------------Moving---------------------------------------
	if(doMove) {
		if (running) {
			if (sound_Move.getBuffer() != sound_running)
				sound_Move.setBuffer(*sound_running);
			if (sound_Move.getStatus() != sf::Sound::Playing)
				sound_Move.play();

			if (!doAttack) {
				animation.setImageCount(7);
				animation.setSwitchTime(0.07f * speed / 160);
				animation.update(direction, *texture_Combat_Running, sprite, deltaTime);
			}
		}
		else {
			if (sound_Move.getBuffer() != sound_walking)
				sound_Move.setBuffer(*sound_walking);
			if (sound_Move.getStatus() != sf::Sound::Playing)
				sound_Move.play();

			if (!doAttack) {
				animation.setImageCount(7);
				animation.setSwitchTime(0.07f * speed / 100);
				animation.update(direction, *texture_Combat_Walking, sprite, deltaTime);
			}
		}

		sf::Vector2f oldPos = sprite.getPosition();

		collisionRect.move(movement);
		sprite.move(movement);

		for (Wall &w : walls) {
			if (collisionRect.getGlobalBounds().intersects(w.collisionRect.getGlobalBounds())) {
				collisionRect.setPosition(oldPos);
				sprite.setPosition(oldPos);
			}
		}
		return true;
	}
	//-----------------------------Not Moving------------------------------------
	else {
		sound_Move.stop();
		if (!doAttack && !doBeenHit) {
			if (sprite.getTexture() != texture_Combat_Stopped)
				sprite.setTexture(*texture_Combat_Stopped);
			sprite.setTextureRect(sf::IntRect(textureWidth * direction, 0, textureWidth, textureHeight));
		}
	}
	//---------------------------------------------------------------------------
	return false;
//---------------------------------------------------------------------------
}

void Player::attack(float deltaTime) {
	if (doAttack) {
		if (hitPicture > 12) {
			hitPicture = 0;
			doAttack = false;
			sound_Hit.stop();
		}
		else {
			if (sound_Hit.getBuffer() != sound_swing)
				sound_Hit.setBuffer(*sound_swing);
			if (sound_Hit.getStatus() != sf::Sound::Playing)
				sound_Hit.play();

			animation.setImageCount(12);
			animation.setSwitchTime(0.07f * attackSpeed / 0.63f);
			if (animation.update(direction, *texture_Combat_Attack, sprite, deltaTime))
				++hitPicture;
		}
	}
}

void Player::beenHit(float deltaTime) {
	if (doBeenHit) {
		if (beenHitPicture > 8 || doMove || doAttack) {
			beenHitPicture = 0;
			doBeenHit = false;
		}
		else if (!doAttack && !doMove) {
			animation.setImageCount(8);
			animation.setSwitchTime(0.08f);
			if (animation.update(direction, *texture_Combat_Been_Hit, sprite, deltaTime))
				++beenHitPicture;
		}
	}
}

void Player::die(float deltaTime) {
	if (doDie) {
		if (diePicture > 8) {
			diePicture = 0;
			doDie = false;
		}
		else {
			animation.setImageCount(8);
			animation.setSwitchTime(0.09f);
			if (animation.update(direction, *texture_Combat_Die, sprite, deltaTime))
				++diePicture;
		}
	}
}

void const Player::draw(sf::RenderWindow &window) const {
	//window.draw(collisionRect);
	window.draw(sprite);
}

void Player::decreaseHealthBy(float _health) {
	health -= _health;
	healthBar.setValue((health / maxHealth) * 100);
}

void Player::decreaseManaBy(float _mana) {
	mana -= _mana;
	manaBar.setValue((mana / maxMana) * 100);
}

void Player::increaseHealthBy(float _health) {
	health += _health;
	healthBar.setValue((health / maxHealth) * 100);
}

void Player::increaseManaBy(float _mana) {
	mana += _mana;
	manaBar.setValue((mana / maxMana) * 100);
}

sf::Uint8 Player::getDirection(void) {
	return direction;
}

float Player::getHealth(void) {
	return health;
}

float Player::getMana(void) {
	return mana;
}

sf::Sprite Player::getSprite(void) {
	return sprite;
}

bool Player::getRunning(void) {
	return running;
}

void Player::setDirection(sf::Uint8 _direction) {
	direction = _direction;
}

void Player::setHealth(float _health) {
	health = _health;
	healthBar.setValue((health / maxHealth) * 100);
}

void Player::setMaxHealth(float _maxHealth) {
	maxHealth = _maxHealth;
}

void Player::setMana(float _mana) {
	mana = _mana;
	manaBar.setValue((mana / maxMana) * 100);
}

void Player::setMaxMana(float _maxmana) {
	maxMana = _maxmana;
}

void Player::setPosition(float x, float y) {
	collisionRect.setPosition(x, y);
	sprite.setPosition(x, y);
}

void Player::setRunning(bool _running) {
	if (_running) {
		speed = 160;
	}
	else
		speed = 100;
	running = _running;
}

void Player::setAttackSpeed(float _attackSpeed) {
	attackSpeed = _attackSpeed;
}

void Player::setSpeed(float _speed) {
	speed = _speed;
}

void Player::setHealthBarPosition(float x, float y) {
	healthBar.setPosition(x, y);
}

void Player::setManaBarPosition(float x, float y) {
	manaBar.setPosition(x, y);
}

void Player::setStoppedTexture(sf::Texture &Texture) {
	texture_stopped = &Texture;
}

void Player::setWalkingTexture(sf::Texture &Texture) {
	texture_walking = &Texture;
}

void Player::setCombat_Attack(sf::Texture &Texture) {
	texture_Combat_Attack = &Texture;
}

void Player::setCombat_Been_Hit(sf::Texture &Texture) {
	texture_Combat_Been_Hit = &Texture;
}

void Player::setCombat_Die(sf::Texture &Texture) {
	texture_Combat_Die = &Texture;
}

void Player::setCombat_Running(sf::Texture &Texture) {
	texture_Combat_Running = &Texture;
}

void Player::setCombat_Stopped(sf::Texture &Texture) {
	texture_Combat_Stopped = &Texture;
}

void Player::setCombat_Walking(sf::Texture &Texture) {
	texture_Combat_Walking = &Texture;
}

void Player::setHealthBarTexture(sf::Texture &Texture) {
	healthBar.setTexture(Texture);
}

void Player::setManaBarTexture(sf::Texture &Texture) {
	manaBar.setTexture(Texture);
}

void Player::setEmptyTexture(sf::Texture &Texture) {
	texture_Empty = &Texture;
}

void Player::setWalking_Sound(sf::SoundBuffer &sound) {
	sound_walking = &sound;
}
void Player::setRunning_Sound(sf::SoundBuffer &sound) {
	sound_running = &sound;
}
void Player::setSwing_Sound(sf::SoundBuffer &sound) {
	sound_swing = &sound;
}