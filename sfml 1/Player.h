#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Wall.h"
#include "CircleBar.h"

#define SQRT_2 std::sqrt(2.f)

class Player
{
public:
	unsigned short id;
	char name[20];
	sf::RectangleShape collisionRect;
	CircleBar healthBar;
	CircleBar manaBar;
	sf::Sprite sprite;
	bool dead;
	bool doAttack;
	bool doMove;
	bool doBeenHit;
	bool doDie;

	Animation animation;

	Player(float, float);
	void const draw(sf::RenderWindow &) const;

	bool move(float, std::vector<Wall *> &);
	void attack(float);
	void beenHit(float);
	void die(float);
	
	sf::Uint8 getDirection(void);
	float getHealth(void);
	float getMana(void);
	sf::Sprite getSprite(void);
	bool getRunning(void);

	void decreaseHealthBy(float);
	void decreaseManaBy(float);
	void increaseHealthBy(float);
	void increaseManaBy(float);

	void setAttackSpeed(float);
	void setDirection(sf::Uint8);
	void setHealth(float);
	void setMaxHealth(float);
	void setMana(float);
	void setMaxMana(float);
	void setHealthBarPosition(float, float);
	void setManaBarPosition(float, float);
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
	void setHealthBarTexture(sf::Texture &);
	void setManaBarTexture(sf::Texture &);
	void setEmptyTexture(sf::Texture &);
	void setWalking_Sound(sf::SoundBuffer &);
	void setRunning_Sound(sf::SoundBuffer &);
	void setSwing_Sound(sf::SoundBuffer &);
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

	sf::SoundBuffer *sound_walking;
	sf::SoundBuffer *sound_running;
	sf::SoundBuffer *sound_swing;
	sf::Sound sound_Move;
	sf::Sound sound_Hit;

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

	float health;
	float maxHealth;
	float mana;
	float maxMana;
	bool running;
	float speed;
	float attackSpeed;
};
