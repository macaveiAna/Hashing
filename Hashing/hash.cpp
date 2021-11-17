/*
* @file:		hash.cpp
* @author:		Ana Macavei
* @version:		1.0
*
* Demonstrates: Creating and testing hash function and evaluating the results
*/

#include <iostream>		//need to test
#include <fstream>		//need to output/write to file
#include <algorithm>	//to use transform() operator
#include <string>

using namespace std;

int hashFunction(string str);

const int SIZE = 45402;

int main() {

	static long hashArray[SIZE];

	for (int i = 0; i < SIZE; i++)
		hashArray[i] = 0;

	std::ifstream inFile;
	inFile.open("words.txt");
	if (!inFile) {
		cout << "open failed";
		return 0;
	}

	unsigned long hash = 0; //initilize hash to 0
	
	string words; //words in the string which is converted to lowercase
	for (int i = 0; i < SIZE; i++) {

		inFile >> words; //inserts the words

		//using transform() function and ::tolower in STL to convert to lowercase
		transform(words.begin(), words.end(), words.begin(), ::tolower);
			
			//create hash from each word using hash function
			hashArray[hashFunction(words)]++;
	
	}


	int collisions = 0; //initialize collisions to 0

	//exporting to csv file
	ofstream outFile("hashresults.csv");
	for (long i = 0; i < SIZE; i++) {

		outFile << i << ',' << hashArray[i] << '\n';

		if (hashArray[i] > 1)//counts collisions if collisions > 1

		//computes the correct number of collisions in the hashArray
		collisions += hashArray[i] - 1; //minus 1 because the first one doesn't count as a collision
		
	}

	//calculating the collision percentage
	double collisionPercentage = static_cast<double>(collisions) / SIZE * 100;

	std::cout << "CS 260: Assignment 6, Ana Macavei, " << collisionPercentage << "%\n";

	inFile.close();
	outFile.close();

	return 0;
}

/*
* A hash function to map values to key
*
* @param	string arr
* @return	hash % SIZE
*/
int hashFunction(string str) {
	
	//non-negative numbers 0-45402
	unsigned long hash = 0;

	int prime = 997;//picked a prime number to use in my hash function

	for (int i = 0; i < str.size(); i++) {

		//my hash function
		hash = (hash * prime) + str[i] * prime * prime /10;
	}
	
	return hash % SIZE;
}






