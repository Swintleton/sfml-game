#include "stdafx.h"
#include "Daemon.h"


Daemon::Daemon(unsigned int id, bool dead, bool running, float speed, float attackSpeed, float maxHealth, float health, float maxMana, float mana, float x, float y, sf::Uint8 direction, sf::Texture &Attack, sf::Texture &Been_Hit, sf::Texture &Die, sf::Texture &Running, sf::Texture &Spawn, sf::Texture &Stopped, sf::Texture &Walking, sf::Texture &texture_Health, sf::Texture &texture_Mana, sf::Font &font, sf::Texture &Empty)
:id(id),dead(dead),running(running),speed(speed),attackSpeed(attackSpeed),maxHealth(maxHealth),maxMana(maxMana),textureWidth(96),textureHeight(96),doMove(false),doAttack(false),doBeenHit(false),hitPicture(0),beenHitPicture(0),diePicture(0),healthBar(x-35, y-58),manaBar(x-35, y-48),animation(textureWidth, textureHeight, 7, 0.07f)
{
	texture_Attack = &Attack;
	texture_Been_Hit = &Been_Hit;
	texture_Die = &Die;
	texture_Running = &Running;
	texture_Spawn = &Spawn;
	texture_Stopped = &Stopped;
	texture_Walking = &Walking;
	texture_Empty = &Empty;

	sprite.setTexture(*texture_Stopped);
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

void Daemon::draw(sf::RenderWindow &window) const {
	window.draw(sprite);
	healthBar.draw(window);
	manaBar.draw(window);
}

void Daemon::move(float deltaTime) {
	if (doMove) {
		if (running && !doAttack) {
			animation.setImageCount(7);
			animation.setSwitchTime(0.07f * speed / 160);
			animation.update(direction, *texture_Running, sprite, deltaTime);
		}
		else if (!doAttack) {
			animation.setImageCount(7);
			animation.setSwitchTime(0.07f * speed / 100);
			animation.update(direction, *texture_Walking, sprite, deltaTime);
		}
		healthBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 58);
		manaBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 48);
		doMove = false;
		notMovedTime = 0;
	}
	else if (!doAttack && !doBeenHit && notMovedTime > 0.2f) {
		sprite.setTexture(*texture_Attack);
		sprite.setTextureRect(sf::IntRect(0, textureHeight * direction, textureWidth, textureHeight));
	}
}

void Daemon::attack(float deltaTime) {
	if (doAttack) {
		if (hitPicture > 8 || doBeenHit) {
			hitPicture = 0;
			doAttack = false;
		}
		else if (doAttack) {
			animation.setImageCount(8);
			animation.setSwitchTime(0.08f * attackSpeed / 0.63f);
			if (animation.update(direction, *texture_Attack, sprite, deltaTime))
				++hitPicture;
		}
	}
}

void Daemon::beenHit(float deltaTime) {
	if (doBeenHit) {
		if (beenHitPicture > 8 || doMove) {
			beenHitPicture = 0;
			doBeenHit = false;
		}
		else if (!doAttack && !doMove) {
			animation.setImageCount(8);
			animation.setSwitchTime(0.08f);
			if (animation.update(direction, *texture_Been_Hit, sprite, deltaTime))
				++beenHitPicture;
		}
	}
}

void Daemon::die(float deltaTime) {
	if (doDie) {
		if (diePicture < 13) {
			animation.setImageCount(12);
			animation.setSwitchTime(0.09f);
			if (animation.update(direction, *texture_Die, sprite, deltaTime))
				++diePicture;
		}
		else if (diePicture == 13)
			++diePicture;
		else {
			sprite.setTexture(*texture_Empty);
			healthBar.setTexture(*texture_Empty);
			healthBar.setText("");
			manaBar.setTexture(*texture_Empty);
			manaBar.setText("");
			diePicture = 0;
			doDie = false;
		}
	}
}

void Daemon::decreaseHealthBy(float _health) {
	health -= _health;
	healthBar.setValue((health / maxHealth) * 100);
	healthBar.setText(health);
}

void Daemon::decreaseManaBy(float _mana) {
	mana -= _mana;
	manaBar.setValue((mana / maxMana) * 100);
	manaBar.setText(mana);
}

void Daemon::increaseHealthBy(float _health) {
	health += _health;
	healthBar.setValue((health / maxHealth) * 100);
	healthBar.setText(health);
}

void Daemon::increaseManaBy(float _mana) {
	mana += _mana;
	manaBar.setValue((mana / maxMana) * 100);
	manaBar.setText(mana);
}

void Daemon::setDirection(sf::Uint8 _direction) {
	direction = _direction;
}

void Daemon::setHealth(float _health) {
	health = _health;
	healthBar.setValue((health / maxHealth) * 100);
	healthBar.setText(health);
}

void Daemon::setMana(float _mana) {
	mana = _mana;
	manaBar.setValue((mana / maxMana) * 100);
	manaBar.setText(mana);
}

void Daemon::setPosition(float x, float y) {
	sprite.setPosition(x, y);
	collisionRect.setPosition(x, y);
	healthBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 58);
	manaBar.setPosition(collisionRect.getPosition().x - 35, collisionRect.getPosition().y - 48);
}