#ifndef BINGOCARD_HPP
# define BINGOCARD_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Bingocard{
public:
	int _card [5][5];

	Bingocard(int grid[25]);
	~Bingocard(){};

	void crossNumber(int num);
	bool checkForWin();
	void calculateAnswer(int num);
};

#endif