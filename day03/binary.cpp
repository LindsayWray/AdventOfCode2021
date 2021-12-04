#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::string	findGamma(std::vector<std::string>  binaries){
	int zeroes;
	int ones;
	std::stringstream ss;

	for(int i = 0; i < 12; i++){
		ones = 0;
		zeroes = 0;
		for(int j = 0; j < 1000; j++){
			if (binaries[j][i] == '1')
				ones++;
			else zeroes++;
		}
		if (ones > zeroes)
			ss << '1';
		else
			ss << '0';
	}
	return ss.str();
}

std::string	findEpsilon(std::vector<std::string>  binaries){
	int zeroes;
	int ones;
	std::stringstream ss;

	for(int i = 0; i < 12; i++){
		ones = 0;
		zeroes = 0;
		for(int j = 0; j < 1000; j++){
			if (binaries[j][i] == '1')
				ones++;
			else zeroes++;
		}
		if (ones < zeroes)
			ss << '1';
		else
			ss << '0';
	}
	return ss.str();
}

int main(){
	std::vector<std::string> binaries;
	std::string binaryString;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do {
		input >> binaryString;
		binaries.push_back(binaryString);
	} while (!input.eof());
	input.close();

	std::string gamma = findGamma(binaries);
	std::cout << "binary: " << gamma << std::endl;
	long gammaDecimal = strtol(gamma.c_str(), NULL, 2);
	std::cout << "decimal: " << gammaDecimal << std::endl;

	std::string epsilon = findEpsilon(binaries);
	std::cout << "binary: " << epsilon << std::endl;
	long epsilonDecimal = strtol(epsilon.c_str(), NULL, 2);
	std::cout << "decimal: " << epsilonDecimal << std::endl;

	long answer = gammaDecimal * epsilonDecimal;
	std::cout << "Final Answer: " << answer << std::endl;
}