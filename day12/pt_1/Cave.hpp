#ifndef CAVE_HPP
# define CAVE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <queue>

class Cave{
	std::string _name;
	std::vector<Cave*> _connections;
	bool	_smallCave;

public:
	Cave(){};
	Cave(std::string name);
	~Cave(){};

	void	addConnection(Cave &cave);
	void	searchPath(std::deque<Cave> path);
};

#endif