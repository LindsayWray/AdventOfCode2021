#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>

typedef struct coordinates{
	int x;
	int y;
	int z;
} coordinates;

typedef coordinates(*permutation)(coordinates);

class Scanner{
public:
	std::vector<coordinates> beacons;
	bool	beaconsAdded;

	void	locatedBeacons();
	void	locatedBeacons(std::vector<coordinates> copyBeacons, coordinates diff);

	void	compareWithSet();
	bool	comparePermutation(std::vector<coordinates> copyBeacons);

	static std::set<coordinates> totalBeacons;

};

#endif