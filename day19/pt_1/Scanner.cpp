#include "Scanner.hpp"

std::set<coordinates> Scanner::totalBeacons;


bool operator<(const coordinates& lhs, const coordinates& rhs)
{
	return (lhs.x < rhs.x) || //|| (lhs.y < rhs.y) || (lhs.z < rhs.z);
	(rhs.x == lhs.x && lhs.y < rhs.y) || 
	(rhs.x == lhs.x && lhs.y == rhs.y && lhs.z < rhs.z);
}

coordinates operator-(const coordinates& lhs, const coordinates& rhs)
{
	coordinates c;
	c.x = lhs.x - rhs.x;
	c.y = lhs.y - rhs.y;
	c.z = lhs.z - rhs.z;
	return c;
}

// coordinates operator+(const coordinates& lhs, const coordinates& rhs)
// {
// 	coordinates c;
// 	c.x = lhs.x + rhs.x;
// 	c.y = lhs.y + rhs.y;
// 	c.z = lhs.z + rhs.z;
// 	return c;
// }

// bool operator==(const coordinates& lhs, const coordinates& rhs)
// {
// 	return (lhs.x == rhs.x && (lhs.y == rhs.y) && lhs.z < rhs.z);
// }

void	Scanner::locatedBeacons(){
	for(int i = 0; i < beacons.size(); i++){
		Scanner::totalBeacons.insert(beacons[i]);
	}
	beaconsAdded = true;
}

void	Scanner::locatedBeacons(std::vector<coordinates> copyBeacons, coordinates diff){
	for(int i = 0; i < copyBeacons.size(); i++){
		Scanner::totalBeacons.insert(copyBeacons[i] - diff);
	}
	beaconsAdded = true;
}


bool	Scanner::comparePermutation(std::vector<coordinates> copyBeacons){
	std::map<coordinates, int> differences;

	for(int i = 0; i < copyBeacons.size(); i++){
		for(std::set<coordinates>::iterator it = Scanner::totalBeacons.begin(); it != Scanner::totalBeacons.end(); it++){
			coordinates diff = copyBeacons[i] - *it;
			if (differences.find(diff) == differences.end()){
				differences.insert(std::make_pair(diff, 1));
			} else {
				differences[diff]++;
				// std::cout << "Found matching diff" << differences[diff] << std::endl;
				if (differences[diff] >= 12){
					//Add diff to all beacons
					// std::cout << "Found 12 matches" << differences[diff] << std::endl;
					locatedBeacons(copyBeacons, diff);
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<coordinates> mutateVector(std::vector<coordinates> original, permutation p) {
	std::vector<coordinates> mutated;
	for (int i = 0; i < original.size(); i++) {
		mutated.push_back(p(original[i]));
	}
	return mutated;
}


coordinates flip0(coordinates c) {
	coordinates flip = {c.x, c.y, c.z};	
	return flip;
	}
coordinates flip1(coordinates c) {coordinates flip = {c.x, -c.y, -c.z}; return flip;}
coordinates flip2(coordinates c) {coordinates flip = {-c.x, c.y, -c.z}; return flip;}
coordinates flip3(coordinates c) {coordinates flip = {-c.x, -c.y, c.z}; return flip;}
coordinates flip4(coordinates c) {coordinates flip = {c.x, c.z, -c.y}; return flip;}
coordinates flip5(coordinates c) {coordinates flip = {c.x, -c.z, c.y}; return flip;}
coordinates flip6(coordinates c) {coordinates flip = {-c.x, c.z, c.y}; return flip;}
coordinates flip7(coordinates c) {coordinates flip = {-c.x, -c.z, -c.y}; return flip;}

coordinates flip8(coordinates c)  {coordinates flip = {c.y, c.z, c.x}; return flip;}
coordinates flip9(coordinates c)  {coordinates flip = {c.y, -c.z, -c.x}; return flip;}
coordinates flip10(coordinates c) {coordinates flip = {-c.y, c.z, -c.x}; return flip;}
coordinates flip11(coordinates c) {coordinates flip = {-c.y, -c.z, c.x}; return flip;}
coordinates flip12(coordinates c) {coordinates flip = {c.y, c.x, -c.z}; return flip;}
coordinates flip13(coordinates c) {coordinates flip = {c.y, -c.x, c.z}; return flip;}
coordinates flip14(coordinates c) {coordinates flip = {-c.y, c.x, c.z}; return flip;}
coordinates flip15(coordinates c) {coordinates flip = {-c.y, -c.x, -c.z}; return flip;}

coordinates flip16(coordinates c) {coordinates flip = {c.z, c.x, c.y}; return flip;}
coordinates flip17(coordinates c) {coordinates flip = {c.z, -c.x, -c.y}; return flip;}
coordinates flip18(coordinates c) {coordinates flip = {-c.z, c.x, -c.y}; return flip;}
coordinates flip19(coordinates c) {coordinates flip = {-c.z, -c.x, c.y}; return flip;}
coordinates flip20(coordinates c) {coordinates flip = {c.z, c.y, -c.x}; return flip;}
coordinates flip21(coordinates c) {coordinates flip = {c.z, -c.y, c.x}; return flip;}
coordinates flip22(coordinates c) {coordinates flip = {-c.z, c.y, c.x}; return flip;}
coordinates flip23(coordinates c) {coordinates flip = {-c.z, -c.y, -c.x}; return flip;}


void	Scanner::compareWithSet(){
	permutation pms[] = {
		flip0,
		flip1,
		flip2,
		flip3,
		flip4,
		flip5,
		flip6,
		flip7,
		flip8,
		flip9,
		flip10,
		flip11,
		flip12,
		flip13,
		flip14,
		flip15,
		flip16,
		flip17,
		flip18,
		flip19,
		flip20,
		flip21,
		flip22,
		flip23,
	};

	for (int i = 0; i < 24; i++) {
		std::vector<coordinates> mutated = mutateVector(beacons, pms[i]);
		// for(int i = 0; i < mutated.size(); i++){
		// 	std::cout << mutated[i].x << "," << mutated[i].y << "," << mutated[i].z << "," << std::endl;
		// }
		if (comparePermutation(mutated)){
			break;
		}
	}



	// for(std::map<coordinates, int>::iterator it = differences.begin(); it != differences.end(); it++){
	// 	std::cout << it->second << std::endl;
	// }
}
