#pragma once

#include "Wall.h"

std::vector<Wall *> walls;
std::vector<sf::RectangleShape *> collisionList;	//ALL THE WALL RectangleShape for collision check ... I do it in the player.ccp
std::vector<sf::Vector2f> playerBeforeWall;			//This 2 contains the coordinates of the collison RectangleShapes...
std::vector<sf::Vector2f> playerBehindWall;
