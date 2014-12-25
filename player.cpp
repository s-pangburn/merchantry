#include "player.h"


Player::Player()
{
	money = 200;		//Starting value
	turns = 30;			//Time before game over
	bodyGuard = false;	//To protect from bandits
}

int Player::getMoney()
{
	return money;
}

void Player::setMoney(int m)
{
	money = m;
}

int Player::getTurns()
{
	return turns;
}

void Player::setTurns(int s)
{
	turns = s;
}

bool Player::hasBodyGuard()
{
	return bodyGuard;
}

void Player::setBodyGuard(bool bg)
{
	bodyGuard = bg;
}