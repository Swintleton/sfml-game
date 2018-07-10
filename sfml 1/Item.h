#pragma once
#include "ResourceManager.h"

//				ITEM TYPES
//WEAPONS					(	0 - 12999		)
//Axes						(	0 - 999			)
//Bows						(	1000 - 1999		)
//Crossbows					(	2000 - 2999		)
//Daggers					(	3000 - 3999		)
#define Dagger				((unsigned short ) 3000)
//Javelins					(	4000 - 4999		)
//Maces						(	5000 - 5999		)
//Polearms					(	6000 - 6999		)
//Scepters					(	7000 - 7999		)
//Spears					(	8000 - 8999		)
//Staves					(	9000 - 9999		)
//Swords					(	10000 - 10999	)
#define Short_Sword			((unsigned short ) 9000)
//Throwing Weapons			(	11000 - 11999	)
//Wands						(	12000 - 12999	)

//ARMORS					(	13000 - 20999	)
//Amulets					(	13000 - 13999	)
#define Amulet_1			((unsigned short ) 12000)
#define Amulet_2			((unsigned short ) 12001)
#define Amulet_3			((unsigned short ) 12002)
//Armours					(	14000 - 14999	)
#define Quilted_Armor		((unsigned short ) 14000)
//Belts						(	15000 - 15999	)
#define Sash				((unsigned short ) 15000)
//Boots						(	16000 - 16999	)
#define Boots				((unsigned short ) 16000)
//Circlets 					(	17000 - 17999	)
#define Circlet				((unsigned short ) 17000)
//Gloves 					(	18000 - 18999	)
#define Leather_Gloves		((unsigned short ) 18000)
//Helms 					(	19000 - 19999	)
#define Cap					((unsigned short ) 19000)
//Rings 					(	20000 - 20999	)
#define Ring_1				((unsigned short ) 20000)
#define Ring_2				((unsigned short ) 20001)
#define Ring_3				((unsigned short ) 20002)
#define Ring_4				((unsigned short ) 20003)
#define Ring_5				((unsigned short ) 20004)

class Item
{
public:
	unsigned int id;
	int owner;
	sf::Vector2i inventorySize;
	sf::Vector2i inventoryPosition;
	sf::RectangleShape collisionRect;
	sf::Sprite sprite;
	sf::Text text;
	char *name;

	unsigned short type;

	bool inInventory;
	bool grabbed;
	bool equipped;

	bool visible;
	unsigned char minusX;
	unsigned char minusY;

	Item(unsigned int id, int owner, unsigned short type, bool visible, bool equipped, bool grabbed, bool inInventory, unsigned char inventoryPositionX, unsigned char inventoryPositionY, float x, float y, Resource &);
	void draw(sf::RenderWindow &window) const;
	//Return values:
	//0	-	Normal update
	//1	-	Grabbing happend
	unsigned char update(sf::RenderWindow &, bool inventoryVisible, sf::Vector2f playerPos);
	void setGroundPosition();
	void setNonGroundPosition();
	void setPosition(float, float);
	void setPosition(sf::Vector2f);
};

