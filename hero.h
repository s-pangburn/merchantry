//Hero class declaration

#pragma once
#include "location.h"

class Hero : public Location
{
public:
	Hero();
	void runEvent(Player &p); //Hiring event
};

