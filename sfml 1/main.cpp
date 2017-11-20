#include "stdafx.h"

#include <sfml\Graphics.hpp>

#include <iostream>
#include <list>
#include <vector>

#include "Player.h"
#include "Animation.h"
#include "Wall.h"

static const float VIEW_HEIGHT = 800.f;

using namespace std;

unsigned int frameCount = 0;

std::list<sf::Sprite *> collisionSpriteList;
std::list<sf::RectangleShape *> collisionList;	//ALL THE WALL RectangleShape for collision check ... I do it in the player.ccp
std::vector<sf::Vector2f> playerBeforeWall;		//This 2 contains the coordinates of the collison RectangleShapes...
std::vector<sf::Vector2f> playerBehindWall;


int main() {
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT-200.f), "SFML 1", sf::Style::Default);
	window.setFramerateLimit(60);

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.f, 600.0f));

//------------------------------CREATE PLAYER & ENVIRONMENT--------------------------------------------------
	sf::Texture texture;
	texture.loadFromFile("Textures/stopped/stopped.bmp");

	Player player(texture, window.getSize().x / 2, window.getSize().y / 2+300);
	texture.loadFromFile("Textures/walking/walking.bmp");
	player.addWalkingTexutre(texture);

	texture.loadFromFile("Textures/walls/wall0.bmp");
	Wall wall1(texture, 250.f, 400.f);
	collisionList.push_back(&wall1.wal);
	playerBehindWall.push_back(wall1.wal.getPosition());
	playerBeforeWall.push_back(sf::Vector2f{ wall1.wal.getPosition().x, wall1.wal.getPosition().y + 60 });
	//if player is behind a wall, then the wall collision RectangleShapes should be lower in y axis
	collisionSpriteList.push_back(&wall1.wall);
	

	Wall wall2(texture, 0.f, 300.f);
	collisionList.push_back(&wall2.wal);
	playerBehindWall.push_back(wall2.wal.getPosition());
	playerBeforeWall.push_back(sf::Vector2f{ wall2.wal.getPosition().x, wall2.wal.getPosition().y + 60 });
	collisionSpriteList.push_back(&wall2.wall);

	Wall wall3(texture, 90.f, 600.f);
	collisionList.push_back(&wall3.wal);
	playerBehindWall.push_back(wall3.wal.getPosition());
	playerBeforeWall.push_back(sf::Vector2f{ wall3.wal.getPosition().x, wall3.wal.getPosition().y + 60 });
	collisionSpriteList.push_back(&wall3.wall);

	Wall wall4(texture, 63.f, 300.f);
	collisionList.push_back(&wall4.wal);
	playerBehindWall.push_back(wall4.wal.getPosition());
	playerBeforeWall.push_back(sf::Vector2f{ wall4.wal.getPosition().x, wall4.wal.getPosition().y + 60 });
	collisionSpriteList.push_back(&wall4.wall);
//-----------------------------------------------------------------------------------------------------------

	/*		I don't really met with this, so I don't want to delete it :/
	for (std::list<sf::RectangleShape *>::iterator i = collisionList.begin(); i != collisionList.end(); ++i)
	cout << *i << " ";
	cout << endl;
	*/

	sf::Clock clock;	//CHECKING FPS
	sf::Clock clock2;	//PLAYER UPDATE ... for player movements...
	sf::Event eventt;

	bool playerBeforeWalls = false;
	int stepper = 0;
	unsigned short closestWall = 0;

	while (window.isOpen())
	{
		//hardcore fps counter
		++frameCount;
		if (clock.getElapsedTime().asSeconds() >= 1.0f) {
			clock.restart();
			cout << "FPS: " << frameCount << endl;
			frameCount = 0;
		}

		while (window.pollEvent(eventt))
		{
			switch (eventt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					view.setSize(VIEW_HEIGHT * (float(window.getSize().x) / float(window.getSize().y)), VIEW_HEIGHT);
					break;
				/*		I will need this later...		I think
				case sf::Event::TextEntered:
					if (eventt.text.unicode < 128) {
						//printf("%c", eventt.text.unicode);
					}
					break;
				*/
			}
		}

		window.clear(sf::Color(150, 150, 150));
		
		player.update(clock2.restart().asSeconds(), collisionList);

		view.setCenter(player.getPositon());
		window.setView(view);

		playerBeforeWalls = false;
		stepper = 0;

		//PUT THE COLLISION RECT UP OR DOWN
		for (sf::RectangleShape *other : collisionList) {
			if (player.getPositon().y < other->getPosition().y) {
				other->setPosition(playerBeforeWall[stepper]);
			}
			if (player.getPositon().y > other->getPosition().y - 30) {	//the -30 only for change quicker
				other->setPosition(playerBehindWall[stepper]);
			}
			++stepper;
		}
		//IF PLAYER IS COLLISIONED WITH A WALL THE DECIDE IT IS BEFORE THE WALL OR NOT
		for (sf::Sprite *other : collisionSpriteList) {
			if (player.player.getGlobalBounds().intersects(other->getGlobalBounds())) {
				if (player.getPositon().y < (other->getPosition().y+(other->getOrigin().y/2)))
					playerBeforeWalls = true;
				else
					playerBeforeWalls = false;
			}
		}
		
		if (playerBeforeWalls)
			player.draw(window);
		wall1.draw(window);
		wall2.draw(window);
		wall3.draw(window);
		wall4.draw(window);
		if(!playerBeforeWalls)
			player.draw(window);

		window.display();
	}
	return 0;
}
