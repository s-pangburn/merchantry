//Location class definiton

#include "location.h"
#include "player.h"
#include <iostream>
using namespace std;

Location::Location()
{
	visited = false;
	id = '.';				//Map icon
	color = "bright white";
	dead = false;
}

bool Location::getVisited()
{
	return visited;
}

void Location::setVisited(bool v)
{
	visited = v;
}

char Location::getID()
{
	if (visited)
	{
		return id;
	}
	else
	{
		return '.'; //Pretend to be a blank tile
	}
}

void Location::setID(char i)
{
	id = i;
}

bool Location::isDead()
{
	return dead;
}

void Location::setDead(bool d)
{
	dead = d;
}

string Location::getColor()
{
	if (visited)
	{
		return color;
	}
	else
	{
		return "grey"; //Pretend to be a blank tile
	}
}

void Location::setColor(string c)
{
	color = c;
}

void Location::runEvent(Player &p)
{
	cout << "The path seems deserted." << endl << endl; 
}

void Location::stringToUpper(string &s)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		s[i] = toupper(s[i]);
	}

}