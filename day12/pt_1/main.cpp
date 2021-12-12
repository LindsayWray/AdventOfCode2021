#include "Cave.hpp"

int main(){
	std::map<std::string, Cave> caves;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	std::string line;
	do {
		input >> line;
		std::replace(line.begin(), line.end(), '-', ' ');
		std::stringstream ss(line);
		std::string caveName1;
		ss >> caveName1;
		if(caves.find(caveName1) == caves.end()){
			Cave cave1(caveName1);
			caves[caveName1] = cave1;
		}
		std::string caveName2;
		ss >> caveName2;
		if(caves.find(caveName2) == caves.end()){
			Cave cave2(caveName2);
			caves[caveName2] = cave2;
		}
		caves[caveName1].addConnection(caves[caveName2]);
		caves[caveName2].addConnection(caves[caveName1]);
	} while (!input.eof());
	input.close();



	caves["start"].searchPath(std::deque<Cave>());

	//std::cout << caves.size() << std::endl;
}