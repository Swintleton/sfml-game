#include "stdafx.h"
#include "Online_Player.h"

Online_Player::Online_Player(unsigned int id, std::string name, bool dead, bool running, float speed, float attackSpeed, float maxHealth, float health, float maxMana, float mana, float x, float y, sf::Uint8 direction, sf::Texture &stopped, sf::Texture &walking, sf::Texture &combat_attack, sf::Texture &combat_been_hit, sf::Texture &combat_die, sf::Texture &combat_running, sf::Texture &combat_stopped, sf::Texture &combat_walking, sf::Texture &texture_Health, sf::Texture &texture_Mana, sf::Font &font, sf::Texture &Empty)
:id(id),name(name),dead(dead),running(running),speed(speed),attackSpeed(attackSpeed),maxHealth(maxHealth),health(health),maxMana(maxMana),mana(mana),direction(direction),textureWidth(96),textureHeight(96),doMove(false),doAttack(false),doBeenHit(false),doDie(false),animation(96, 96, 7, 0.07f), hitPicture(0),beenHitPicture(0),diePicture(0),healthBar(x-35,y-58),manaBar(x-35,y-48)
{
	texture_stopped = &stopped;
	texture_walking = &walking;
	texture_Combat_Attack = &combat_attack;
	texture_Combat_Been_Hit = &combat_been_hit;
	texture_Combat_Die = &combat_die;
	texture_Combat_Running = &combat_running;
	texture_Combat_Stopped = &combat_stopped;
	texture_Combat_Walking = &combat_walking;
	texture_Empty = &Empty;

	sprite.setTexture(*texture_stopped);
	sprite.setOrigin(textureWidth / 2.f, textureHeight / 2.f);
	sprite.setPosition(x, y);
	sprite.setTextureRect(sf::IntRect(0, 0, textureWidth, textureHeight));

	collisionRect.setPosition(x, y);
	collisionRect.setSize(sf::Vector2f{ 26, 44 });
	collisionRect.setOrigin(13, 22);

	healthBar.setTexture(texture_Health);
	healthBar.setFont(font);
	setHealth(health);
	manaBar.setTexture(texture_Mana);
	manaBar.setFont(font);
	setMana(mana);
}

void Online_Player::move(float deltaTime)
{
	if (doMove) {
		if (running && !doAttack) {
			animation.setImageCount(7);
			animation.setSwitchTime(0.07f * speed / 160);
			animation.update(direction, *texture_Combat_Running, sprite, deltaTime);
		}
		else if (!doAttack) {
			animation.setImageCount(7);
			animation.setSwitchTime(0.07f * speed / 100);
			animation.update(direction, *texture_Combat_Walking, sprite, deltaTime);
		}
		healthBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 58);
		manaBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 48);
		doMove = false;
	}
	else if(!doAttack && !doBeenHit) {
		sprite.setTexture(*texture_Combat_Stopped);
		sprite.setTextureRect(sf::IntRect(textureWidth * direction, 0, textureWidth, textureHeight));
	}
}

void Online_Player::attack(float deltaTime) {
	if (hitPicture > 12) {
		hitPicture = 0;
		doAttack = false;
	}
	else if (doAttack) {
		animation.setImageCount(12);
		animation.setSwitchTime(0.07f * attackSpeed / 0.63f);
		if (animation.update(direction, *texture_Combat_Attack, sprite, deltaTime))
			++hitPicture;
	}
}

void Online_Player::beenHit(float deltaTime) {
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

void Online_Player::die(float deltaTime) {
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

void const Online_Player::draw(sf::RenderWindow &window) const {
	//window.draw(collisionRect);
	window.draw(sprite);
}

void Online_Player::decreaseHealthBy(float _health) {
	health -= _health;
	healthBar.setValue((health / maxHealth) * 100);
	healthBar.setText(health);
}

void Online_Player::decreaseManaBy(float _mana) {
	mana -= _mana;
	manaBar.setValue((mana / maxMana) * 100);
	manaBar.setText(mana);
}

void Online_Player::increaseHealthBy(float _health) {
	health += _health;
	healthBar.setValue((health / maxHealth) * 100);
	healthBar.setText(health);
}

void Online_Player::increaseManaBy(float _mana) {
	mana += _mana;
	manaBar.setValue((mana / maxMana) * 100);
	manaBar.setText(mana);
}

sf::Uint8 Online_Player::getDirection() {
	return direction;
}

float Online_Player::getHealth() {
	return health;
}

float Online_Player::getMana() {
	return mana;
}

const sf::Vector2f Online_Player::getPosition() {
	return collisionRect.getPosition();
}

sf::Sprite Online_Player::getSprite(void) {
	return sprite;
}

bool Online_Player::getRunning(void) {
	return running;
}

void Online_Player::setDirection(sf::Uint8 _direction) {
	direction = _direction;
}

void Online_Player::setHealth(float _health) {
	health = _health;
	healthBar.setValue((health / maxHealth) * 100);
	healthBar.setText(health);
}

void Online_Player::setMaxHealth(float _maxHealth) {
	maxHealth = _maxHealth;
}

void Online_Player::setMana(float _mana) {
	mana = _mana;
	manaBar.setValue((mana / maxMana) * 100);
	manaBar.setText(mana);
}

void Online_Player::setMaxMana(float _maxmana) {
	maxMana = _maxmana;
}

void Online_Player::setPosition(float x, float y) {
	collisionRect.setPosition(x, y);
	sprite.setPosition(x, y);
	healthBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 58);
	manaBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 48);
}

void Online_Player::setRunning(bool _running) {
	if (_running) {
		speed = 160;
	}
	else
		speed = 100;
	running = _running;
}

void Online_Player::setSpeed(float _speed) {
	speed = _speed;
}

void Online_Player::setStoppedTexture(sf::Texture &Texture) {
	texture_stopped = &Texture;
}

void Online_Player::setWalkingTexture(sf::Texture &Texture) {
	texture_walking = &Texture;
}


void Online_Player::setCombat_Attack(sf::Texture &Texture) {
	texture_Combat_Attack = &Texture;
}

void Online_Player::setCombat_Been_Hit(sf::Texture &Texture) {
	texture_Combat_Been_Hit = &Texture;
}

void Online_Player::setCombat_Die(sf::Texture &Texture) {
	texture_Combat_Die = &Texture;
}

void Online_Player::setCombat_Running(sf::Texture &Texture) {
	texture_Combat_Running = &Texture;
}

void Online_Player::setCombat_Stopped(sf::Texture &Texture) {
	texture_Combat_Stopped = &Texture;
}

void Online_Player::setCombat_Walking(sf::Texture &Texture) {
	texture_Combat_Walking = &Texture;
}
