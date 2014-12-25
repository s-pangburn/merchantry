//Player class definition

#pragma once


class Player
{
public:
	Player();
	int getMoney();
	void setMoney(int m);
	int getTurns();
	void setTurns(int s);
	bool hasBodyGuard();
	void setBodyGuard(bool bg);
private:
	int money;
	int turns;
	bool bodyGuard;
};

