//Game function definitions

#include "game.h"
#include "farmer.h"
#include "bandit.h"
#include "hero.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

Game::Game()
{
	ifstream file;
	char tile;

	file.open("levels.txt");

	if (file.fail())
	{
		cout << "Error, could not find level data! Abort!" << endl;
		system("pause");
		exit(0);
	}
	
	file >> rows >> cols;

	//CREATE DYNAMICALLY ALLOCATED 2D ARRAY
	grid = new Location**[rows];		//Pointer to an array of pointers...

	for (int i = 0; i < rows; i++)
	{
		grid[i] = new Location*[cols];	//Each pointer in the array points to another array to create a dynamic 2D array
	}

	//FILL THE ARRAY WITH STUFF FROM THE FILE
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			file >> tile;
			if (tile == '.')
			{
				grid[i][j] = new Location;
			}
			else if (tile == 'f')
			{
				grid[i][j] = new Farmer;
			}
			else if (tile == 'b')
			{
				grid[i][j] = new Bandit;
			}
			else if (tile == 'h')
			{
				grid[i][j] = new Hero;
			}
			else if (tile == 'p')
			{
				//Set player starting position in addition to creating a blank tile
				playerX = j;
				playerY = i;
				grid[i][j] = new Location;
				grid[i][j]->setVisited(true);
			}
		}
	}

	file.close();
}

void Game::start()
{
	drawIntro();	//Story introductory paragraph
	drawGrid();		//Draw map

	srand(time(0)); //Set random seed

	do
	{
		makeMove(); //Game loop

	} while (p.getTurns() > 0 && p.getMoney() < GOAL);

	checkWin();		//Did the player win or lose?
}

void Game::drawIntro()
{
	cout << endl << "Welcome to ";

	setTextColor("bright white");
	cout << "Merchantry Destiny VII!";		//Every time the text cuts off like this, this is me changing the text color.
	setTextColor("NULL");
		
	cout << endl << "------------------------------------" << endl << endl;

	cout << "  You are ";

	setTextColor("yellow");
	cout << "Fip Fop McMurchannt";
	setTextColor("NULL");

	cout << ", youngest in a long line of ";

	setTextColor("light aqua");
	cout << "sandal merchants";
	setTextColor("NULL");

	cout << "." << endl << endl;
	cout << "  One day, you wake up to find your house completely empty. It seems a lowly" << endl;

	setTextColor("red");
	cout << "  bandit";
	setTextColor("NULL");

	cout << " had broken in!" << endl << endl;
	cout << "  You're grateful to be alive, but ";

	setTextColor("aqua");
	cout << "the landlord will be here tomorrow";
	setTextColor("NULL");

	cout << ", and you \n  have no money to pay your rent of ";

	setTextColor("yellow");
	cout << GOAL << " gold";
	setTextColor("NULL");

	cout << "!" << endl << endl;
	cout << "  Luckily, the thief had no interest in your sandal stocks. Looks like you'll \n  have to make your way around town and make back that money!" << endl;

	cout << endl;
	
	setTextColor("bright white");
	system("pause");
	setTextColor("NULL");
	system("CLS"); //Clear the screen
}

void Game::drawGrid()
{
	cout << "---------------" << endl << "| Merchantry! |" << endl << "---------------" << endl; //Title

	//HUD
	setTextColor("yellow");
	cout << "   Money: " << p.getMoney() << "G/" << GOAL << endl;        
	
	if (p.hasBodyGuard())
	{
		setTextColor("bright green");
		cout << "   Adventurer bodyguard!";
	}

	//Preparing the grid
	setTextColor("bright white");
	cout << endl;
	indent(INDENT);

	for (int i = 0; i <= cols; i++)
	{
		cout << "--"; //Top border
	}

	cout << endl;
	indent(INDENT);


	for (int i = 0; i < rows; i++)
	{
		cout << "|"; //Left border
		setTextColor("grey");


		for (int j = 0; j < cols; j++)
		{

			if (j == playerX && i == playerY)
			{
				setTextColor("yellow");
				cout << " #"; //Print player icon if this location contains the player.
			}
			else
			{
				setTextColor(grid[i][j]->getColor());	//Get the location's drawing color
				cout << " " << grid[i][j]->getID();		//Get the location's character
			}
		}
		
		setTextColor("bright white");
		cout << "|";

		if (i == 0) //If it is the end of the first row, draw a bit more of the HUD
		{
			if (p.getTurns() > 5)
			{
				setTextColor("Light Aqua");
			}
			else
			{
				setTextColor("Red");
			}
			cout << " Hours left until rent: " << p.getTurns();
		}

		setTextColor("bright white");	
		cout << endl;
		indent(INDENT); //Indent the map
	}
	
	setTextColor("bright white");

	for (int i = 0; i <= cols; i++)
	{
		cout << "--";  //Bottom border
	}
	cout << endl << endl;

	setTextColor("NULL");
}

void Game::makeMove()
{
	string choice;
	
	do
	{
		cout << "What direction do you want to move in, North, South, East, or West? ";
		getline(cin, choice);

		stringToUpper(choice);		//Convert to uppercase

		p.setTurns(p.getTurns()-1);	//Subtract an hour from the time the player has left

		if (choice == "NORTH" || choice == "UP" || choice == "N" || choice == "U")
		{
			if (validMove(playerX, playerY-1))
			{
				playerY -= 1;										//Move the player
				system("CLS");										//Clear the console
				drawGrid();
				grid[playerY][playerX]->setVisited(true);			//Set the new space to visited
				setTextColor(grid[playerY][playerX]->getColor());	//Color the event text based on the "theme" of the new tile
				grid[playerY][playerX]->runEvent(p);				//Run the tile's event
				setTextColor("NULL");
			}
			else
			{
				p.setTurns(p.getTurns()+1);							//If the move wasn't valid, set the number of turns back to what it was
			}
		}
		else if (choice == "SOUTH" || choice == "DOWN" || choice == "S" || choice == "D")
		{
			if (validMove(playerX, playerY+1))
			{
				playerY += 1;
				system("CLS");
				drawGrid();
				grid[playerY][playerX]->setVisited(true);
				setTextColor(grid[playerY][playerX]->getColor());
				grid[playerY][playerX]->runEvent(p);
				setTextColor("NULL");
			}
			else
			{
				p.setTurns(p.getTurns()+1);
			}
		}
		else if (choice == "WEST" || choice == "LEFT" || choice == "W" || choice == "L")
		{
			if (validMove(playerX-1, playerY))
			{
				playerX -= 1;
				system("CLS");
				drawGrid();
				grid[playerY][playerX]->setVisited(true);
				setTextColor(grid[playerY][playerX]->getColor());
				grid[playerY][playerX]->runEvent(p);
				setTextColor("NULL");
			}
			else
			{
				p.setTurns(p.getTurns()+1);
			}
		}
		else if (choice == "EAST" || choice == "RIGHT" || choice == "E" || choice == "R")
		{
			if (validMove(playerX+1, playerY))
			{
				playerX += 1;
				system("CLS");
				drawGrid();
				grid[playerY][playerX]->setVisited(true);
				setTextColor(grid[playerY][playerX]->getColor());
				grid[playerY][playerX]->runEvent(p);
				setTextColor("NULL");
			}
			else
			{
				p.setTurns(p.getTurns()+1);
			}
		}
		else
		{
			//Invalid input
			setTextColor("red");
			cout << endl << "Invalid choice. Enter something else." << endl << endl;
			setTextColor("NULL");
			p.setTurns(p.getTurns()+1); //Reset number of turns

			choice = "repeat"; //Loop
		}
	} while (choice == "repeat");
	
}

void Game::checkWin()
{
	system("CLS");  //Clear the console
	drawGrid();

	if (p.getMoney() > GOAL) //The player won
	{
		setTextColor("bright green");
		cout << "You made enough money to cover rent! Congratulations!" << endl << endl;
	}
	else  //The player lost
	{
		setTextColor("red");
		cout << "You didn't make enough money in time! Game Over!" << endl << endl;
	}
	setTextColor("NULL");

	system("pause");
}

bool Game::validMove(int x, int y)
{
	if (x < 0 || x >= cols || y < 0 || y >= rows) //Out of bounds
	{
		cout << endl << "You hit a wall." << endl << endl;
		return false;
	}
	return true;
}

void Game::indent(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		cout << " ";
	}
}

void Game::setTextColor(string color)
{
	//NOTE: #include <windows.h> library
	//Available colors: Black, Grey, (Bright) White, (Light) Blue, (Light) Green, (Light) Aqua, (Dark) Red, Purple, (Dark) Yellow, Pink

	stringToUpper(color);

	if (color == "BLACK")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0); //This function was written to replace this ugly thing
	}
	else if (color == "BLUE")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	}
	else if (color == "GREEN")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	}
	else if (color == "AQUA")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	}
	else if (color == "DARK RED")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	}
	else if (color == "PURPLE")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	}
	else if (color == "DARK YELLOW")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	}
	else if (color == "WHITE" || color == "DEFAULT" || color == "NULL")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (color == "GREY" || color == "GRAY")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	}
	else if (color == "LIGHT BLUE" || color == "BRIGHT BLUE")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	}
	else if (color == "LIGHT GREEN" || color == "BRIGHT GREEN")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	}
	else if (color == "LIGHT AQUA" || color == "BRIGHT AQUA")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	}
	else if (color == "RED" || color == "BRIGHT RED")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	}
	else if (color == "PINK" || color == "BRIGHT PINK")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	}
	else if (color == "YELLOW" || color == "BRIGHT YELLOW")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	}
	else if (color == "BRIGHT WHITE" || color == "LIGHT WHITE")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else
	{
		cout << "Error, invalid color input. Abort!" << endl;
		system("pause");
		exit(0);
	}
}

void Game::stringToUpper(string &s)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		s[i] = toupper(s[i]);
	}

}
