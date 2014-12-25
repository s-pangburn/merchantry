//Farmer class declaration

#pragma once
#include "location.h"

class Farmer : public Location
{
public:
	Farmer();
	void runEvent(Player &p); //Haggling minigame
};

