#include "Scanner.hpp"

void	compareScanners(std::vector<Scanner> scanners){
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

	std::cout << Scanner::totalBeacons.size() << std::endl;

	// for(std::set<coordinates>::iterator i = Scanner::totalBeacons.begin(); i != Scanner::totalBeacons.end(); i++){
	// 	std::cout << i->x << " " << i->y << " " << i->z << std::endl;
	// }

	//std::cout << scanners[0].beacons[0].x << std::endl;
}