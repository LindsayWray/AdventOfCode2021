#include <iostream>
#include <fstream>
#include <vector>

unsigned int	countIncreases(std::vector<int> numVector){
	unsigned int len = numVector.size();
	unsigned int count = 0;

	for(int i = 1; i < (len - 2); i++){
		if ((numVector[i] + numVector[i + 1] + numVector[i + 2]) >  
			(numVector[i - 1] + numVector[i] + numVector[i + 1]))
			count++;
	}
	return count;
}

int main(){
	std::vector<int> numVector;
	int num;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do {
		input >> num;
		numVector.push_back(num);
	} while (!input.eof());
	input.close();

	unsigned int answer = countIncreases(numVector);
	std::cout << answer << std::endl;
}