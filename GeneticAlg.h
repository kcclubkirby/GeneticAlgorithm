/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP480											*
*Week 3 Lab Assignment									*
*Date: 7/25/13											*
*GeneticAlg.h											*
*-------												*
*This file contains the header info and implementation	*
*for the genetic algorithm.								*
*-------------------------------------------------------*/
#include <iostream>
#include <random>
#include <string>
using namespace std;

//~~~~~~~~~~~~~~~~~~~~~
//popMember
//~~~~~~~~~~~~~~~~~~~~~
//This struct is used for each member of the population
struct popMember
{
	string sentence; //the string in the population
	int displacement; //The displacement used in the fitness function
	int correctNum; //The number of correct characters
};

//~~~~~~~~~~~~~~~~~~~~~
//DeleteElement
//~~~~~~~~~~~~~~~~~~~~~
//This function will take a vector of popMember structs
//And delete the entry indicated by placement, move the
//vector elements in front of that entry to fill the gap
//and finally decrement the size of the vector.
void DeleteElement(vector<popMember>& vec, int placement)
{
	for (int i = placement; i < vec.size(); i++) //Start at the place indicated
	{
		if (i + 1 == vec.size()) //If we have reached the end of the vector
			vec.resize(vec.size() - 1); //Decrement the vector size
		else
			vec[i] = vec[i + 1]; //Otherwise, move the elements backwards
	}
	return;
}

//~~~~~~~~~~~~~~~~~~~~~
//GenAlg
//~~~~~~~~~~~~~~~~~~~~~
//This class is the genetic algorithm object
//It will iterate through a string, randomly changing
//the characters as it gets closer to the solution
class GenAlg
{
public:
	GenAlg(){}; //Constructor
	~GenAlg(){}; //Destructor
	void Init(); //Initializer
	void CreatePop(); //This method will create/randomize the population string
	void Iterate(int num, int iter); //This method recusively iterates through the algorithm
	void Reset(); //This method will reset the string
private:
	vector<popMember> population; //This holds the population
	string solution; //This holds the solution string
	int stringLength; //This holds the length of the string
	int populationSize; //This holds the size of the population
};

//Init
//This method initializes the algorithm
void GenAlg::Init()
{
	stringLength = 28; //Set the string length
	populationSize = 100; //Set the size of the population
	population.resize(populationSize);
	solution = "genetic algorithms can be fun"; //Set the solution
	CreatePop(); //Create the population
}

//CreatePop
//This method will create/randomize the population string
void GenAlg::CreatePop()
{
	//Create a character string
	char* character;
	character = new char;
	character[1] = '\0';

	//Iterate through the population
	for (int i = 0; i < populationSize; i++)
	{
		for (int j = 0; j < stringLength + 1; j++)
		{
			character[0] = rand() % 94 + 32; //Randomize the character
			if (population[i].sentence.size() != solution.size()) //If the string hasn't been created yet
				population[i].sentence.append(character); //Add it to the end of the string
			else  
				population[i].sentence[j] = character[0]; //Change the character to the random character
		}
	}
}

//Iterate
//This method is a recursive function which will iterate through the algorithm
void GenAlg::Iterate(int num, int iter)
{
	iter++; //Increase the iteration
	if (num < 1) //If we have reached the final iteration
	{
		//Give up
		cout << "Solution not found after " << iter - 1 << " iterations." << endl << endl;
		return;
	}

	//-------------------
	//FITNESS FUNCTION
	//-------------------
	for (int i = 0; i < populationSize; i++) //Move through the population
	{
		//Count the displacement and number of correct characters
		population[i].displacement = 0;
		population[i].correctNum = 0;
		for (int j = 0; j < population[i].sentence.size(); j++) //Go through the sentence
		{
			//Add to the displacement if the character is incorrect
			if (population[i].sentence[j] > solution[j])
				population[i].displacement += population[i].sentence[j] - solution[j];
			else if (population[i].sentence[j] < solution[j])
				population[i].displacement += solution[j] - population[i].sentence[j];
			//Otherwise, add to the number of correct characters
			else
				population[i].correctNum++;
		}
	}

	//Order the list from "closest to solution" to "furthest from solution"
	vector<popMember> orderedPop; //This will hold the ordered list
	orderedPop.resize(population.size());  //Set the size of the list
	int count = 0; //This will keep count of where we are in the ordered list
	int completePercentage = 0; //This will hold an incredibly large number to help with random selection
	while (population.size() != 0) //Until the population is empty
	{
		int highestPower = 0; //Keep track of the highest number of correct characters
		int lowestDisplacement = -1; //Keep track of the item with the lowest displacement
		for (int i = 0; i < population.size(); i++) //Move through the population
		{
			if (population[i].correctNum > highestPower) //If we have reached a higher number
			{
				highestPower = population[i].correctNum; //Change the number accordingly
				lowestDisplacement = -1; //Reset the displacement
			}
			if (population[i].correctNum == highestPower)
			{
				//Set the displacement, if we reach a lower number
				if (lowestDisplacement == -1)
					lowestDisplacement = population[i].displacement;
				else if (lowestDisplacement > population[i].displacement)
					lowestDisplacement = population[i].displacement;
			}
		}
		for (int i = 0; i < population.size(); i++) //Move through the population
		{
			//Find the best entry in the population
			if (population[i].correctNum == highestPower &&
				population[i].displacement == lowestDisplacement)
			{
				//Add its value to the complete percentage
				completePercentage += ((2000 + 2000 * population[i].correctNum) - population[i].displacement);
				orderedPop[count] = population[i]; //Add it to the list
				DeleteElement(population, i); //Delete that element from the population

				i--; //Decrement the iterator
				count++; //Increment the counter
			}
		}
	}
	population = orderedPop; //Save the ordered list back into the population

	//Show the top four tries along with the iteration number
	if (iter == 1)
		cout << "We start with these top four tries:" << endl;
	else
		cout << "The top four tries for iteration " << iter - 1 << ":" << endl;
	for (int i = 0; i < 4; i++)
		cout << population[i].sentence
			<< " -- Disp: " << population[i].displacement
			<< " -- # Correct: " << population[i].correctNum << endl;
	cout << endl;

	//Check if we found the correct sentence
	if (population[0].sentence == solution)
		cout << "Solution found at iteration " << iter - 1 << "!" << endl << endl;
	else //If not, then continue with the genetic algorithm
	{
		//-------------------
		//SELECTION
		//-------------------
		vector<popMember> newPopulation; //This will hold the new selected population
		newPopulation.resize(population.size()); //Set the size of the list
		int iterator = 0; //Create an iterator for the list
		while (iterator < newPopulation.size()) //Until the iterator reaches the end of the new population
		{
			int random = rand() % completePercentage; //Select a random item in the list using the percentage
			for (int i = 0; i < population.size(); i++) //Iterate through the population until you find the one selected
			{
				//Use subtraction to find the selected element
				random -= ((2000 + 2000 * population[i].correctNum) - population[i].displacement);

				if (random < 0) //If it is found
				{
					newPopulation[iterator] = population[i]; //Place it in the new population
					i = population.size(); //Stop iterating through the population
					iterator++; //Increment the overall iterator
				}
			}
		}
		population = newPopulation; //Save the new population into the regular population

		//-------------------
		//CROSSOVER
		//-------------------
		for (int i = 0; i < population.size(); i++) //Move through the population
		{
			string result; //This will hold the resulting string
			result = population[i].sentence; //Set it eual to the first string
			int crossoverPoint = rand() % (stringLength + 1); //Find a random crossover point
			for (int j = crossoverPoint; j < stringLength + 1; j++) //Starting at the crossover point...
				population[i].sentence[j] = population[i + 1].sentence[j]; //change every character after that to the second string
			i++; //Increment through the list twice
		}

		//-------------------
		//MUTATION
		//-------------------
		for (int i = 0; i < population.size(); i++) //Move through the population
		{
			int mutationPoint = rand() % (stringLength + 2); //Find a random point to mutate
			if (mutationPoint != stringLength + 1) //As long as there is a mutation point
				population[i].sentence[mutationPoint] = rand() % 94 + 32; //Randomize the character
		}

		//Continue through the genetic algorithm to the next iteration
		Iterate(num - 1, iter); 
	}
	return;
}

//Reset
//This method will reset the character string
void GenAlg::Reset()
{
	//Create a character string
	char* character;
	character = new char;
	character[1] = '\0';

	//Iterate through the population
	for (int i = 0; i < populationSize; i++)
	{
		for (int j = 0; j < stringLength + 1; j++)
		{
			character[0] = rand() % 94 + 32; //Randomize the character
			population[i].sentence[j] = character[0]; //Change the character to the random character
		}
	}
}