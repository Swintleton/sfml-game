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

	texture.loadFromFile("Textures/walls/wall1.bmp");
	walls.push_back(Wall(texture, 500.f, 490.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 50));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	walls.push_back(Wall(texture, 563.f, 490.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 50));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	walls.push_back(Wall(texture, 626.f, 490.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 50));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	walls.push_back(Wall(texture, 500.f, 600.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 50));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	walls.push_back(Wall(texture, 563.f, 600.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 50));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	walls.push_back(Wall(texture, 626.f, 600.f, 4));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 50));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);

	texture.loadFromFile("Textures/walls/wall0.bmp");
	walls.push_back(Wall(texture, 750.f, 520.f, 0));
	playerBeforeWall.push_back(sf::Vector2f(walls.back().collisionRect.getPosition().x, walls.back().collisionRect.getPosition().y + 40));
	playerBehindWall.push_back(walls.back().collisionRect.getPosition());
	collisionList.push_back(&walls.back().collisionRect);
	//-----------------------------------------------------------------------------------------------------------

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

		view.setCenter(player.collisionRect.getPosition());
		window.setView(view);

		//playerBeforeWalls = false;
		stepper = 0;

		//PUT THE COLLISION RECT UP OR DOWN
		for (sf::RectangleShape *other : collisionList) {
			if (player.collisionRect.getPosition().y < other->getPosition().y + 30)
				other->setPosition(playerBeforeWall[stepper]);
			if (player.collisionRect.getPosition().y > other->getPosition().y - 30)	//the -30 only for change quicker
				other->setPosition(playerBehindWall[stepper]);
			++stepper;
		}

		//IF PLAYER IS BEFORE THE WALL OR NOT
		for (Wall &other : walls) {
			if (player.collisionRect.getGlobalBounds().intersects(other.getSprite().getGlobalBounds())) {
				if (player.collisionRect.getPosition().y < other.collisionRect.getPosition().y) {
					other.beforePlayer = true;
				}
				else
					other.beforePlayer = false;
			}
		}

		for (Wall wal : walls) {
			if(!wal.beforePlayer)
				wal.draw(window);
		}
		player.draw(window);
		for (Wall wal : walls) {
			if (wal.beforePlayer)
				wal.draw(window);
		}

		window.display();
	}
	return 0;
}