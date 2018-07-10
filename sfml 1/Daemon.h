#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "RectBar.h"

class Daemon
{
public:
	unsigned int id;
	sf::RectangleShape collisionRect;
	RectBar healthBar;
	RectBar manaBar;
	sf::Sprite sprite;
	bool dead;
	bool doAttack;
	bool doMove;
	bool doBeenHit;
	bool doDie;
	float notMovedTime;

	Daemon(unsigned int id, bool dead, bool running, float speed, float attackSpeed, float maxHealth, float health, float maxMana, float mana, float x, float y, sf::Uint8 direction, sf::Texture &texture_Attack, sf::Texture &texture_Been_Hit, sf::Texture &texture_Die, sf::Texture &texture_Running, sf::Texture &texture_Spawn, sf::Texture &texture_Stopped, sf::Texture &texture_Walking, sf::Texture &texture_Health, sf::Texture &texture_Mana, sf::Font &font, sf::Texture &texture_Empty);
	void draw(sf::RenderWindow &) const;

	void attack(float);
	void move(float);
	void beenHit(float);
	void die(float);

	void decreaseHealthBy(float);
	void decreaseManaBy(float);
	void increaseHealthBy(float);
	void increaseManaBy(float);

	void setDirection(sf::Uint8);
	void setHealth(float);
	void setMana(float);
	void setPosition(float x, float y);
private:
	float maxHealth;
	float health;
	float maxMana;
	float mana;
	bool running;
	float speed;
	float attackSpeed;

	//DIRECTIONS:
	//	0	-	RIGHT
	//	1	-	UP
	//	2	-	UP RIGHT
	//	3	-	UP LEFT
	//	4	-	DOWN
	//	5	-	DOWN RIGHT
	//	6	-	DOWN LEFT
	//	7	-	LEFT
	sf::Uint8 direction;

	unsigned short textureWidth;
	unsigned short textureHeight;

	char hitPicture;
	char beenHitPicture;
	char diePicture;

	sf::Texture *texture_Attack;
	sf::Texture *texture_Been_Hit;
	sf::Texture *texture_Die;
	sf::Texture *texture_Running;
	sf::Texture *texture_Spawn;
	sf::Texture *texture_Stopped;
	sf::Texture *texture_Walking;
	sf::Texture *texture_Empty;

	Animation animation;
};

