//Bandit class declaration

#pragma once
#include "location.h"


class Bandit : public Location
{
public:
	Bandit();
	void runEvent(Player &p); //Mugging event
};

