/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP480											*
*Week 3 Lab Assignment									*
*Date: 7/24/13											*
*DTiscareno_Lab3.cpp									*
*-------												*
*This file contains the main implementation	of a genetic*
*algorithm test driver.									*
*-------------------------------------------------------*/
#include "TestDriver.h"

int main()
{
	TestDriver game;
	game.Init(); //Initialize the game
	while (!game.QuitGame()) //Run the game
	{
		game.Update();
	}
	return 0;
}