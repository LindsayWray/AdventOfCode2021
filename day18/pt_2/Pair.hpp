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
	static bool explosions;

	Pair(std::stringstream &ss);
	Pair(Pair *pair1, Pair *pair2);
	Pair(int left, int right);
	Pair(Pair const& original) {
		_leftNum = original._leftNum;
		_rightNum = original._rightNum;
		if (original._left)
			_left = new Pair(*original._left);
		else
			_left = NULL;

		if (original._right)
			_right = new Pair(*original._right);
		else
			_right = NULL;
	}

	~Pair(){};

	bool	explode(int level);
	bool	split();
	std::string toString();
	long magitude();

};

#endif