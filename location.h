//Location class declaration

#pragma once

#include "player.h"
#include <string>
using namespace std;

class Location
{
public:
	Location();
	bool getVisited();
	void setVisited(bool v);
	char getID();
	void setID(char i);
	string getColor();								//Used with Game::setTextColor()
	void setColor(string c);
	bool isDead();
	void setDead(bool d);
	virtual void runEvent(Player &p);
	void stringToUpper(string &s);
protected:
	static const bool TOGGLE_VISIBILITY = false;	//DEBUGGING PURPOSES ONLY, will reveal map layout at outset.
private:
	bool visited;
	string color;									//Used with Game::setTextColor(), map icon color
	char id;										//Map icon
	bool dead;										//Whether the event at this space is "dead", no longer functioning.
};

