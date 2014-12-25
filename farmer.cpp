#include "farmer.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

Farmer::Farmer()
{
	setVisited(TOGGLE_VISIBILITY);
	setID('V');						//Map icon
	setColor("bright white");
	setDead(false);
}

void Farmer::runEvent(Player &p)
{
	string choice;
	int price = rand()%800 + 200; //Villager's proposed buying price
	int proposal;

	if (!isDead())
	{
		cout << "It's a humble villager! What will you do?" << endl << endl;
		do
		{
			cout << "  SELL sandals, or LEAVE? ";
			getline(cin, choice);

			stringToUpper(choice); //Convert to uppercase

			cout << endl;

			if (choice == "SELL" || choice == "SELL SANDALS" || choice == "S")
			{
				cout << "The villager says they would love some sandals, and proposes \nbuying them for " << price << "G." << endl << endl;
				do
				{
					cout << "  ACCEPT the offer or HAGGLE? ";
					getline(cin, choice);
					stringToUpper(choice);

					if (choice == "ACCEPT" || choice == "A" || choice == "YES" || choice == "Y")
					{
						p.setMoney(p.getMoney()+price); //Add funds

						cout << endl << "\"It was a pleasure doing business with you!\" says the villager as \nhe bids you farewell." << endl;

						setDead(true);		//Villager leaves
						choice = "LEAVE";	//End loop
					}
					else if (choice == "HAGGLE" || choice == "H")
					{
						cout << endl << "Name your price: ";
						cin >> proposal;

						while (cin.fail() || proposal < 0) //Input validation
						{
							cout << "Invalid input, try again: ";
							cin.clear();
							cin.ignore(numeric_limits<int>::max(),'\n'); //I don't know what this does. I'll ask about it later.
							cin >> proposal;
						}

						cin.clear();
						cin.ignore(numeric_limits<int>::max(),'\n');
						
						cout << endl;

						if (proposal > price + (rand()%100 + 100)) //Added risk to haggling upwards
						{
							cout << "The villager seems upset at your exorbitant price! He leaves in a huff." << endl;
						}
						else
						{
							cout << "The villager accepts your offer! You sold a pair of sandals for " << proposal << "G!" << endl;
							p.setMoney(p.getMoney()+proposal);
						}

						setDead(true);		//Villager leaves
						choice = "LEAVE";	//End loop
					}
					else
					{
						//Invalid input (Haggling)
						cout << endl << "The villager doesn't quite understand what you mean. \nDo you accept the offer or not? " << endl << endl;
					}
				} while (choice != "LEAVE");

				
			}
			else if (choice != "LEAVE" && choice != "L")
			{
				//Invalid input (Selling)
				cout << "The villager seems confused. \"I'm sorry sir, could you say that again?\"" << endl;
			}
			cout << endl;

		} while (choice != "LEAVE" && choice != "L");
	}
	else
	{
		//You already sold to this villager
		cout << "It seems that the villager left..." << endl << endl;
	}
}