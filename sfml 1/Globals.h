#pragma once
#include "FpsCounter.h"
#include "Player.h"
#include "Inventory.h"
#include "Online_Player.h"
#include "Wall.h"
#include "Safezone.h"
#include "Regenerator.h"
#include "MessageBox.h"
#include "Daemon.h"
#include "Label.h"
#include "Button_K.h"

static Resource resource;

static bool quit = false;
static bool login = false;
static bool ready = false;
static sf::Mutex globalMutex;

static FpsCounter fpsCounter;

static Player player(0, 0);
static Inventory inventory(player.getSprite().getPosition());
static std::vector<Item> items;

static MessageBox messageBox;
static MessageList messageList;

static std::vector<Online_Player> OPlayers;
static std::vector<Daemon> daemons;

static std::vector<Wall> walls;
static std::vector<Safezone> safezones;
static std::vector < Regenerator> regenerators;
static std::vector<sf::Vector2f> playerBeforeWall;			//This 2 contains the coordinates of the collison RectangleShapes...
static std::vector<sf::Vector2f> playerBehindWall;

static Label dieMessage;
static Button_K respawn_Button;