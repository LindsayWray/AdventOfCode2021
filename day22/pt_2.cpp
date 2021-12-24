#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>

typedef struct cuboid{
	long long minX, maxX, minY, maxY, minZ, maxZ;
	bool state;
} cuboid;

long max(long value1, long value2) {
	if (value1 > value2)
		return value1;
	else 
		return value2;
}

long min(long value1, long value2) {
	if (value1 < value2)
		return value1;
	else 
		return value2;
}


void	splitCuboids(cuboid toAdd, std::list<cuboid> &tinyCuboids){
	for(std::list<cuboid>::iterator it = tinyCuboids.begin(); it != tinyCuboids.end(); it++){
		if (toAdd.maxX < it->minX || it->maxX < toAdd.minX || toAdd.maxY < it->minY || it->maxY < toAdd.minY || toAdd.maxZ < it->minZ || it->maxZ < toAdd.minZ) 
			continue;
		cuboid toSplit = *it;
		std::list<cuboid> splitted;
		if (toAdd.minX > toSplit.minX) {
			cuboid c = {toSplit.minX, toAdd.minX - 1, toSplit.minY, toSplit.maxY, toSplit.minZ, toSplit.maxZ, true};
			tinyCuboids.push_back(c);
		}
		if (toAdd.maxX < toSplit.maxX) {
			cuboid c = {toAdd.maxX + 1, toSplit.maxX, toSplit.minY, toSplit.maxY, toSplit.minZ, toSplit.maxZ, true};
			tinyCuboids.push_back(c);
		}
		if (toAdd.minY > toSplit.minY) {
			cuboid c = {max(toSplit.minX, toAdd.minX), min(toSplit.maxX, toAdd.maxX), toSplit.minY, toAdd.minY - 1, toSplit.minZ, toSplit.maxZ, true};
			tinyCuboids.push_back(c);
		}
		if (toAdd.maxY < toSplit.maxY) {
			cuboid c = {max(toSplit.minX, toAdd.minX), min(toSplit.maxX, toAdd.maxX), toAdd.maxY + 1, toSplit.maxY, toSplit.minZ, toSplit.maxZ, true};
			tinyCuboids.push_back(c);
		}
		if (toAdd.minZ > toSplit.minZ) {
			cuboid c = {max(toSplit.minX, toAdd.minX), min(toSplit.maxX, toAdd.maxX), max(toSplit.minY, toAdd.minY), min(toSplit.maxY, toAdd.maxY), toSplit.minZ, toAdd.minZ - 1, true};
			tinyCuboids.push_back(c);
		}
		if (toAdd.maxZ < toSplit.maxZ) {
			cuboid c = {max(toSplit.minX, toAdd.minX), min(toSplit.maxX, toAdd.maxX), max(toSplit.minY, toAdd.minY), min(toSplit.maxY, toAdd.maxY), toAdd.maxZ + 1, toSplit.maxZ, true};
			tinyCuboids.push_back(c);
		}
		tinyCuboids.erase(it);
	}
	if (toAdd.state)
		tinyCuboids.push_back(toAdd);
}

int main(){
	std::list<cuboid> cuboids;
	std::list<cuboid> tinyCuboids;
	
	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		cuboid c;
		std::string state;
		input >> state;
		c.state = state == "on" ? true : false;
		std::string coordinates;
		input >> coordinates;
		std::stringstream ss(coordinates);
		ss.ignore(2);
		ss >> c.minX;
		ss.ignore(2);
		ss >> c.maxX;
		ss.ignore(3);
		ss >> c.minY;
		ss.ignore(2);
		ss >> c.maxY;
		ss.ignore(3);
		ss >> c.minZ;
		ss.ignore(2);
		ss >> c.maxZ;
		cuboids.push_back(c);
	}while(!input.eof());

	// for(std::list<cuboid>::iterator it = cuboids.begin(); it != cuboids.end(); it++){
	// 	std::cout << it->state << "  " << it->minX << " " << it->maxX << "  " << it->minY << " " << it->maxY << "  " << it->minZ << " " << it->maxZ << std::endl; 
	// }

	for(std::list<cuboid>::iterator it = cuboids.begin(); it != cuboids.end(); it++){
		splitCuboids(*it, tinyCuboids);
	}

	long long answer = 0;
	for(std::list<cuboid>::iterator it = tinyCuboids.begin(); it != tinyCuboids.end(); it++){
		// std::cout << it->state << "  " << it->minX << " " << it->maxX << "  " << it->minY << " " << it->maxY << "  " << it->minZ << " " << it->maxZ << std::endl; 
		answer += (it->maxX - it->minX + 1) * (it->maxY - it->minY + 1) * (it->maxZ - it->minZ + 1);
	}

	std::cout << answer << std::endl;
}