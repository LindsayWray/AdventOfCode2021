#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string>	removeZeroes(std::vector<std::string>  binaries, int index){
	std::vector<std::string>  newBinaries;
	
	for(int i = 0; i < binaries.size(); i++){
		if (binaries[i][index] == '1'){
			newBinaries.push_back(binaries[i]);
		}
	}
	return newBinaries;
}

std::vector<std::string>	removeOnes(std::vector<std::string>  binaries, int index){
	std::vector<std::string>  newBinaries;
	
	for(int i = 0; i < binaries.size(); i++){
		if (binaries[i][index] == '0'){
			newBinaries.push_back(binaries[i]);
		}
	}
	return newBinaries;
}

std::string	findOxygen(std::vector<std::string>  binaries){
	int zeroes;
	int ones;

	for(int i = 0; i < 12; i++){
		ones = 0;
		zeroes = 0;
		for(int j = 0; j < binaries.size(); j++){
			if (binaries[j][i] == '1')
				ones++;
			else zeroes++;
		}
		if (ones >= zeroes){
			binaries = removeZeroes(binaries, i);
		}	
		else
			binaries = removeOnes(binaries, i);
		if (binaries.size() == 1)
			return (binaries[0]);
	}
	return "";
}

std::string	findCO2(std::vector<std::string>  binaries){
	int zeroes;
	int ones;

	for(int i = 0; i < 12; i++){
		ones = 0;
		zeroes = 0;
		for(int j = 0; j < binaries.size(); j++){
			if (binaries[j][i] == '1')
				ones++;
			else zeroes++;
		}
		if (ones < zeroes){
			binaries = removeZeroes(binaries, i);
		}	
		else
			binaries = removeOnes(binaries, i);
		if (binaries.size() == 1)
			return (binaries[0]);
	}
	return "";
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

	std::string oxygen = findOxygen(binaries);
	std::cout << "binary oxygen: " << oxygen << std::endl;
	long decimalOxygen = strtol(oxygen.c_str(), NULL, 2);
	std::cout << "decimal oxygen: " << decimalOxygen << std::endl;

	std::string CO2 = findCO2(binaries);
	std::cout << "binary CO2: " << CO2 << std::endl;
	long decimalCO2 = strtol(CO2.c_str(), NULL, 2);
	std::cout << "decimal CO2: " << decimalCO2 << std::endl;

	long answer = decimalCO2 * decimalOxygen;
	std::cout << "answer: " << answer << std::endl;


}
