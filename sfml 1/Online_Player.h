#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "RectBar.h"

#define SQRT_2 std::sqrt(2.f)

class Online_Player
{
public:
	unsigned int id;
	std::string name;
	sf::RectangleShape collisionRect;
	RectBar healthBar;
	RectBar manaBar;
	sf::Sprite sprite;
	bool dead;
	bool doAttack;
	bool doMove;
	bool doBeenHit;
	bool doDie;

	Animation animation;

	Online_Player(unsigned int id, std::string name, bool dead, bool running, float speed, float attackSpeed, float maxHealth, float health, float maxMana, float mana, float x, float y, sf::Uint8 direction, sf::Texture &stopped, sf::Texture &walking, sf::Texture &combat_attack, sf::Texture &combat_been_hit, sf::Texture &combat_die, sf::Texture &combat_running, sf::Texture &combat_stopped, sf::Texture &combat_walking, sf::Texture &texture_Health, sf::Texture &texture_Mana, sf::Font &font, sf::Texture &texture_Empty);
	void const draw(sf::RenderWindow &) const;

	void move(float);
	void attack(float);
	void beenHit(float);
	void die(float);

	sf::Uint8 getDirection();
	float getHealth();
	float getMana();
	const sf::Vector2f getPosition();
	sf::Sprite getSprite(void);
	bool getRunning(void);

	void decreaseHealthBy(float);
	void decreaseManaBy(float);
	void increaseHealthBy(float);
	void increaseManaBy(float);

	void setDirection(sf::Uint8);
	void setHealth(float);
	void setMaxHealth(float);
	void setMana(float);
	void setMaxMana(float);
	void setPosition(float, float);
	void setRunning(bool);
	void setSpeed(float);

	void setStoppedTexture(sf::Texture &);
	void setWalkingTexture(sf::Texture &);
	void setCombat_Attack(sf::Texture &);
	void setCombat_Been_Hit(sf::Texture &);
	void setCombat_Die(sf::Texture &);
	void setCombat_Running(sf::Texture &);
	void setCombat_Stopped(sf::Texture &);
	void setCombat_Walking(sf::Texture &);
private:
	sf::Texture *texture_stopped;
	sf::Texture *texture_walking;
	sf::Texture *texture_Combat_Attack;
	sf::Texture *texture_Combat_Been_Hit;
	sf::Texture *texture_Combat_Die;
	sf::Texture *texture_Combat_Running;
	sf::Texture *texture_Combat_Stopped;
	sf::Texture *texture_Combat_Walking;
	sf::Texture *texture_Empty;

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

	float maxHealth;
	float health;
	float maxMana;
	float mana;
	bool running;
	float speed;
	float attackSpeed;
};