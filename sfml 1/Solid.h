#pragma once


#include "Wall.h"

std::list<Wall> walls;
std::list<sf::RectangleShape *> collisionList;	//ALL THE WALL RectangleShape for collision check ... I do it in the player.ccp
std::vector<sf::Vector2f> playerBeforeWall;		//This 2 contains the coordinates of the collison RectangleShapes...
std::vector<sf::Vector2f> playerBehindWall;