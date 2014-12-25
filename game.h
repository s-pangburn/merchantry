//Game class declaration

#pragma once

#include "location.h"
#include <string>
using namespace std;

class Game
{
public:
	Game();								//Constructor: Loads from data file
	void start();						//Kicks off the game
	void drawIntro();					//Draws introductory paragraph
	void drawGrid();					//Draws the map
	void makeMove();
	bool validMove(int x, int y);		//Prevents going through walls
	void setTextColor(string color);	//Shortcut function
	void stringToUpper(string &s);		//Converts a string to uppercase
	void indent(int amount);			//Used for indenting the interface consistently
	void checkWin();
private:
	Location*** grid;                   //Triple Pointer Nightmare!
	Player p;
	int rows;
	int cols;
	int playerX;                        //Player COLUMN position
	int playerY;                        //Player ROW position
	
	static const int INDENT = 6;
	static const int GOAL = 3000;		//Monetary goal to win the game
};

