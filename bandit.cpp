//Bandit class definition

#include "bandit.h"
#include <iostream>
using namespace std;

Bandit::Bandit()
{
	setVisited(TOGGLE_VISIBILITY);
	setID('B');							//Map icon
	setColor("red");
	setDead(false);
}

void Bandit::runEvent(Player &p)
{
	string choice;
	bool loop;

	if (!isDead())
	{
		if (p.hasBodyGuard()) //If the player has hired a Hero, avoid this event once.
		{
			cout << "A bandit stops you and demands money!" << endl << endl;
			cout << "The adventurer fights off the bandit while you escape, but she is left behind!" << endl << endl;
			p.setBodyGuard(false);
			setDead(true);
		}
		else
		{
			cout << "A bandit stops you and demands money! What will you do? " << endl << endl;

			do
			{
				loop = false; //Reset looping criteria

				cout << "  Give MONEY, give SANDALS, ATTACK, or RUN? ";
				getline(cin, choice);

				stringToUpper(choice); //Convert to uppercase

				cout << endl;

				if (choice == "MONEY" || choice == "GIVE MONEY" || choice == "M")
				{
					if (p.getMoney() > 300) //If the player has more than 300 gold
					{
						cout << "The bandit takes 300G and tells you to scram." << endl;
						p.setMoney(p.getMoney()-300);
					}
					else if (p.getMoney() > 0)
					{
						cout << "The bandit takes all of your money and tells you to scram." << endl;
						p.setMoney(0);
					}
					else
					{
						cout << "The bandit, seeing you don't have any money, takes a bunch of your sandals instead." << endl;
					}
				}
				else if (choice == "SANDALS" || choice == "GIVE SANDALS" || choice == "S")
				{
					
					if (p.getMoney() > 1000) //Essentially a "get out of jail free" card if the player is poor enough
					{
						cout << "The bandit looks at you angrily and demands money anyway. You lost 400G." << endl;
						p.setMoney(p.getMoney()-400);  //But you lose a little more if you try with too much money.
					}
					else
					{
						cout << "The bandit cackles at how poor you are and decides to take pity on you. \nHe takes a bunch of your sandals and tells you to scram." << endl;
					}
				}
				else if (choice == "ATTACK") //Joke option
				{
					cout << "The bandit shoves you to the ground, \"You thought you could take me? Ahahaha!\"" << endl ;
					cout << "He takes all your money and demands you crawl away on your hands and knees, \nwhich you do. ";
					p.setMoney(0);
					cout << endl;
				}
				else if (choice == "RUN" || choice == "R")
				{
					int dropped = rand()%400 + 100; //Drop a random amount, adding risk to running away

					cout << "You just barely manage to escape, ";
					if (p.getMoney() > dropped)
					{
						cout << "but you dropped "<< dropped << "G.";
						p.setMoney(p.getMoney()-dropped);
					}
					else if (p.getMoney() > 0)
					{
						cout << "but you dropped all of your money!";
						p.setMoney(0);
					}
					else
					{
						cout << "but you're still broke.";
					}
					cout << endl;
				}
				else 
				{
					//Invalid input
					cout << "The bandit looks at you with a baffled look on his face, but once again demands money." << endl;
					loop = true;
				}
				cout << endl;

			} while (loop);
		}
	}
	else
	{
		//A bodyguard killed this bandit earlier
		cout << "There is a dead bandit here..." << endl << endl;
	}
}