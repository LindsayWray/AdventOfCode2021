#include "Scanner.hpp"


void	compareScanners(std::vector<Scanner> &scanners){
	bool everythingAdded = false;

	while(!everythingAdded) {
		everythingAdded = true;
		for(int i = 0; i < scanners.size(); i++) {
			if (scanners[i].beaconsAdded)
				continue;
			everythingAdded = false;
			scanners[i].compareWithSet();
			std::cout << "Comparing: " << i << ", totalBeacons size = " << Scanner::totalBeacons.size() << std::endl; 
		}
	}
}


int		calculateDistance(std::vector<Scanner> &scanners){
	int max = 0;

	for(int i = 0; i < scanners.size(); i++){
		for(int j = 0; j < scanners.size(); j++){
			std::cout << "XYZ = " << scanners[i].location.x << " " << scanners[i].location.y << " " << scanners[i].location.z << std::endl;
			int x = abs(scanners[i].location.x - scanners[j].location.x);
			int y = abs(scanners[i].location.y - scanners[j].location.y);
			int z = abs(scanners[i].location.z - scanners[j].location.z);
			std::cout << "xyz = " << x << " " << y << " " << z << std::endl;

			if (x + y + z > max)
				max = x + y + z;
		}
	}
	return max;
}

int main(){
	std::vector<Scanner> scanners;

	std::ifstream input("../input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		std::string line;
		std::getline(input, line);
		Scanner scanner;
		while(1){
			std::getline(input, line);
			if (line == "" || input.eof())
				break;
			std::stringstream ss(line);
			coordinates coordinate;
			ss >> coordinate.x;
			ss.ignore();
			ss >> coordinate.y;
			ss.ignore();
			ss >> coordinate.z;
			scanner.beacons.push_back(coordinate);
		}
		scanner.beaconsAdded = false;
		scanners.push_back(scanner);
	} while(!input.eof());
	input.close();

	scanners[0].locatedBeacons();
	compareScanners(scanners);

	//std::cout << Scanner::totalBeacons.size() << std::endl;

	int distance = calculateDistance(scanners);
	std::cout << distance << std::endl;

	// for(std::set<coordinates>::iterator i = Scanner::totalBeacons.begin(); i != Scanner::totalBeacons.end(); i++){
	// 	std::cout << i->x << " " << i->y << " " << i->z << std::endl;
	// }

	//std::cout << scanners[0].beacons[0].x << std::endl;
}