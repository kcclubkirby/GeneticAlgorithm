/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP480											*
*Week 3 Lab Assignment									*
*Date: 7/24/13											*
*TestDriver.h											*
*-------												*
*This file contains the header info and implementation	*
*for the test driver.									*
*-------------------------------------------------------*/
#include <iostream>
#include <random>
#include <time.h>
#include "GeneticAlg.h"
using namespace std;

//~~~~~~~~~~~~~~~~~~~~~
//TestDriver
//~~~~~~~~~~~~~~~~~~~~~
//This class is the test driver for the application.
//It will allow the user to choose menu options, and it
//will contain the genetic algorithm.
class TestDriver
{
public:
	TestDriver(){}; //Constructor
	~TestDriver(){}; //Destructor
	void Init(); //Initializes the test driver
	void Update(); //Updates the test driver and/or game
	bool QuitGame(); //Will return true if the game should quit
private:
	int menuState; //Holds the menu state value for the FSM
	int moveNum; //Holds the number of moves made by the player
	bool quitGame; //Will be true if the game should quit
	GenAlg algorithm; //An instance of the genetic algorithm object
	vector < vector < vector<int >> > moveList; //Holds the moves made by the player
};

//Init
//This method will initialize the variables for the test driver class
void TestDriver::Init()
{
	menuState = 0; //Start the menuState at the main menu
	quitGame = false; //The game should not quit at start
	srand(time(NULL)); //seed random generator
	algorithm.Init(); //Initialize the algorithm
}

//Update
//This method will update variables for the test driver and ask for
//user input
void TestDriver::Update()
{
	bool readyToCont = false; //This becomes true when a valid number has been chosen by the user

	if (menuState == 0) //Main Menu
	{
		//Intro text
		cout << "Welcome to the Genetic Algorithm game by David Tiscareno!" << endl
			<< endl
			<< "0) Main Menu" << endl
			<< "1) Begin Genetic Algorithm" << endl
			<< "2) Quit Game"
			<< endl;

		while (!readyToCont) //Wait for a valid input
		{
			//Ask for input
			cin >> menuState;
			cout << endl;
			if (menuState == 0) //Main Menu
				readyToCont = true;
			else if (menuState == 1) //Begin Genetic Algorithm
				readyToCont = true;
			else if (menuState == 2) //Quit Game
			{
				quitGame = true; //Quit the game
				readyToCont = true;
			}
			else
			{
				cout << "Welcome to the Genetic Algorithm game by David Tiscareno!" << endl
					<< endl
					<< "0) Main Menu" << endl
					<< "1) Begin Genetic Algorithm" << endl
					<< "2) Quit Game"
					<< endl;
			}
		}
	}
	else if (menuState == 1) //Begin Genetic Algorithm
	{
		int iterations; //This is the number of iterations the algorithm will run through
		readyToCont = false; //This becomes true when a valid number has been chosen by the user
		cout << "We will take a list of 100 random strings and use a genetic algorithm" << endl
			<< "to merge and mutate and reach a solution!" << endl << endl
			<< "How many times do you want the algorithm to iterate? ";
		while (!readyToCont)
		{
			cin >> iterations; //Input the iterations
			cout << endl;
			if (iterations > 0) //Continue as long as the iterations are greater than zero
				readyToCont = true;
			else
				cout << "Please input a non-negative, non-zero number: ";
		}

		//Run through the algorithm
		algorithm.Iterate(iterations, 0);
		algorithm.Reset(); //Then reset

		menuState = 0; //Go back to main menu
	}
}

//QuitGame
//This method returns the quitGame variable
bool TestDriver::QuitGame()
{
	return quitGame;
}