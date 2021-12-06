#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void passDay(long long ages[9]) {
	long long newFish = ages[0];
	ages[0] = ages[1];
	ages[1] = ages[2];
	ages[2] = ages[3];
	ages[3] = ages[4];
	ages[4] = ages[5];
	ages[5] = ages[6];
	ages[6] = ages[7] + newFish;
	ages[7] = ages[8];
	ages[8] = newFish;
}

int main() {
	std::string ageString;
	long long ages[9] = {0,0,0,0,0,0,0,0,0};

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	input >> ageString;

	std::stringstream ss(ageString);
	for (int num; ss >> num;){
		ages[num]++;
		if (ss.peek() == ',')
			ss.ignore();
	}

	for (int i = 0; i < 256; i++) {
		passDay(ages);
	}

	long long total = 0;
	for (int i = 0; i < 9; i++) {
		total += ages[i];
	}

	std::cout << total << std::endl;
}
