#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


void	passDay(std::vector<int> &ages){
	long len = ages.size();
	for(long i = 0; i < len; i++){
		if (ages[i] == 0){
			ages[i] = 6;
			ages.push_back(8);
		}
		else
			ages[i]--;
	}
}

int main(){
	std::string ageString;
	std::vector<int> ages;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	input >> ageString;
	input.close();

	std::stringstream ss(ageString);
	for (int num; ss >> num;){
		ages.push_back(num);
		if (ss.peek() == ',')
			ss.ignore();
	}

	for(int i = 0; i < 80; i++)
		passDay(ages);
	long long answer = ages.size();
	std::cout << answer << std::endl;
}