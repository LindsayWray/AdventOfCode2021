#ifndef PAIR_HPP
#define PAIR_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Pair{
private:
	int _leftNum;
	Pair* _left;
	int _rightNum;
	Pair* _right;


public:
	static int *leftNeighbour;
	static int rightValueToAdd;


	Pair(std::stringstream &ss);
	Pair(Pair *pair1, Pair *pair2);
	~Pair(){};

	bool	explode(int level);
	std::string toString();

};

#endif