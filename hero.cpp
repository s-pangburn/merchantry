#include "hero.h"
#include <iostream>
#include <string>
using namespace std;

Hero::Hero()
{
	setVisited(TOGGLE_VISIBILITY);
	setID('A');						//Map icon
	setColor("light green");
	setDead(false);
}

void Hero::runEvent(Player &p)
{
	if (!isDead())
	{
		string choice;
		cout << "A noble adventurer crosses your path! What will you do?" << endl << endl;
		do
		{
			cout << "  SELL sandals, HIRE as a bodyguard, ROB for gold, or LEAVE? ";
			getline(cin, choice);

			stringToUpper(choice);

			cout << endl;

			if (choice == "SELL" || choice == "SELL SANDALS" || choice == "S")
			{
				//The adventurer will not buy them unless you are poor enough
				if (p.getMoney() < 1000)
				{
					cout << "The adventurer doesn't need sandals, but seeing how poor you are, \nshe takes pity on you and buys some anyway for 500G." << endl;
					p.setMoney(p.getMoney()+500);
					setDead(true);
					choice = "LEAVE";
				}
				else
				{
					cout << "She doesn't seem all that interested in your sandals." << endl;
				}
			}
			else if (choice == "HIRE" || choice == "HIRE AS BODYGUARD" || choice == "HIRE AS A BODYGUARD" || choice == "H")
			{
				if (!p.hasBodyGuard()) //Don't allow the option if the player has already hired another hero
				{
					cout << "She agrees to protect you for 200G. (YES or NO?) ";
					getline(cin, choice);
					stringToUpper(choice);

					if (choice == "Y" || choice == "YES")
					{
						if (p.getMoney() >= 200)
						{
							p.setBodyGuard(true);
							p.setMoney(p.getMoney() - 200);
							cout << endl << "You paid 200G. The adventurer agreed to protect you from bandits." << endl;
							setDead(true);		//Inactive tile
							choice = "LEAVE";	//End loop
						}
						else
						{
							cout << endl << "But you don't have the money! Too bad!" << endl;
						}
					}
					else if (choice == "N" || choice == "NO")
					{
						cout << endl << "The adventurer shrugs and asks if you need anything else." << endl;
						//Loop
					}
				}
				else
				{
					cout << "The adventurer refuses your offer seeing that you already have a bodyguard." << endl;
				}
			}
			else if (choice == "ROB" || choice == "ROB FOR GOLD" || choice == "R") //Joke choice
			{
				cout << "The adventurer is angry, \"Dirty knave! I'll cut you down!\"" << endl << endl;
				cout << "You just barely manage to escape... ";
				if (p.getMoney() > 50)
				{
					cout << "but you dropped 50G.";
					p.setMoney(p.getMoney()-50);
				}
				else if (p.getMoney() > 0)
				{
					cout << "but you dropped all of your money!";
					p.setMoney(0);
				}
				cout << endl;
				setDead(true);
				choice = "LEAVE";

			}
			else if (choice != "LEAVE" && choice != "L")
			{
				//Invalid input
				cout << "The adventurer is not sure she understands your gibberish." << endl;
			}
			cout << endl;

		} while (choice != "LEAVE" && choice != "L");
	}
	else
	{
		//Whether you angered her or hired her for protection...
		cout << "The adventurer is no longer here." << endl << endl;
	}
}