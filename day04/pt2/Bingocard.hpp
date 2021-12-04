#ifndef BINGOCARD_HPP
# define BINGOCARD_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Bingocard{
private:
	int _card [5][5];
	bool _done;

public:
	Bingocard(int grid[25]);
	~Bingocard(){};

	void crossNumber(int num);
	bool checkForWin();
	void calculateAnswer(int num);

	static long _answer;
};

#endif