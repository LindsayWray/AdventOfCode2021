#include "Cave.hpp"

int pathCount = 0;

Cave::Cave(std::string name) : _name(name){
	if(std::islower(name[0]))
		_smallCave = true;
	else
		_smallCave = false;
}

void	Cave::addConnection(Cave &cave){
	_connections.push_back(&cave);
}

void	Cave::searchPath(std::deque<Cave> path, bool smallCaveSelected){
	// std::cout << "this cave: " << _name << std::endl;
	// for(int i = 0; i < _connections.size(); i++){
	// 	std::cout << _connections[i]->_name << std::endl;
	// }
	//std::cout << std::endl;
	if(_smallCave){
		for(int i = 0; i < path.size(); i++){
			if(path[i]._name == _name){
				if(smallCaveSelected || _name == "start")
					return;
				else
					smallCaveSelected = true;
			}
		}
	}
	if (_name == "end"){
		pathCount++;
		std::cout << pathCount << std::endl;
		return;
	}
	path.push_back(*this);
	for(int i = 0; i < _connections.size(); i++)
		_connections[i]->searchPath(path, smallCaveSelected);
}