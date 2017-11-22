#include "stdafx.h"

#include <iostream>

#include "Player.h"
#include "Solid.h"

static const float VIEW_HEIGHT = 800.f;

using namespace std;

unsigned int frameCount = 0;

int main() {
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT-200), "SFML 1", sf::Style::Default);
	window.setFramerateLimit(60);

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.f, 600.0f));

//------------------------------CREATE PLAYER & ENVIRONMENT--------------------------------------------------
	sf::Texture texture;
	texture.loadFromFile("Textures/stopped/stopped.bmp");

	Player player(texture, window.getSize().x / 2.f, window.getSize().y / 2.f+300);
	texture.loadFromFile("Textures/walking/walking.bmp");
	player.addWalkingTexutre(texture);

	texture.loadFromFile("Textures/walls/wall0.bmp");
	walls.push_back(Wall(texture, 500.f, 445.f, 0));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 30));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	texture.loadFromFile("Textures/walls/wall0.bmp");
	walls.push_back(Wall(texture, 584.f, 420.f, 0));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 30));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	texture.loadFromFile("Textures/walls/wall1.bmp");
	walls.push_back(Wall(texture, 500.f, 600.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 60));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	texture.loadFromFile("Textures/walls/wall1.bmp");
	walls.push_back(Wall(texture, 563.f, 600.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 60));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	texture.loadFromFile("Textures/walls/wall1.bmp");
	walls.push_back(Wall(texture, 626.f, 600.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 60));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);
	//-----------------------------------------------------------------------------------------------------------

	/*
	for (std::list<sf::RectangleShape *>::iterator i = collisionList.begin(); i != collisionList.end(); ++i)
	cout << *i << " ";
	cout << endl;
	*/

	sf::Clock clock;	//CHECKING FPS
	sf::Clock clock2;	//PLAYER UPDATE ... for player movements...
	sf::Event eventt;

	bool playerBeforeWalls = false;
	int stepper = 0;

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

		//playerBeforeWalls = false;
		stepper = 0;

		//PUT THE COLLISION RECT UP OR DOWN
		for (sf::RectangleShape *other : collisionList) {
			if (player.getPositon().y < other->getPosition().y + 30)
				other->setPosition(playerBeforeWall[stepper]);
			if (player.getPositon().y > other->getPosition().y - 30)	//the -30 only for change quicker
				other->setPosition(playerBehindWall[stepper]);
			++stepper;
		}
		//IF PLAYER IS COLLISIONED WITH A WALL THE DECIDE IT IS BEFORE THE WALL OR NOT
		for (Wall other : walls) {
			if (player.getSprite().getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
				if ((player.getPositon().y-30) < other.getSprite().getPosition().y) {
					playerBeforeWalls = true;
					break;
				}
				else {
					playerBeforeWalls = false;
				}
			}
		}
		if(playerBeforeWalls)
			player.draw(window);
		for (Wall wal : walls) {
				wal.draw(window);
		}
		if (!playerBeforeWalls)
			player.draw(window);

		window.display();
	}
	return 0;
}