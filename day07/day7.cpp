#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int	calculate(std::vector<int> crabPos){
	std::vector<int> counters;
	int max = *std::max_element(crabPos.begin(), crabPos.end());
	long long dsitance;
	for(int i = 0; i < max; i++){
		long long count = 0;
		for(int j = 0; j < crabPos.size(); j++){
			count += abs(crabPos[j] - i);
		}
		counters.push_back(count);
	}
	int min = *std::min_element(counters.begin(), counters.end());
	return min;
}

int main(){
	std::string crabString;
	std::vector<int> crabPos;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	input >> crabString;
	input.close();

	std::stringstream ss(crabString);
	for (int num; ss >> num;){
		crabPos.push_back(num);
		if (ss.peek() == ',')
			ss.ignore();
	}
	int answer = calculate(crabPos);
	std::cout << "answer is: " << answer << std::endl;
}