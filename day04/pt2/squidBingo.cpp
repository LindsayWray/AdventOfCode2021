#include "Bingocard.hpp"

int main(){
	std::vector<Bingocard> bingocards;
	std::string drawstring;
	int card [25];
	std::vector<int> draws;

	std::ifstream input("../input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	input >> drawstring;

	std::stringstream ss(drawstring);
	for (int num; ss >> num;){
		draws.push_back(num);
		if (ss.peek() == ',')
			ss.ignore();
	}
	
	do {
		for(int i = 0; i < 25; i++){
			input >> card[i];
		}
		bingocards.push_back(Bingocard(card));
	} while (!input.eof());
	input.close();
	
	for (int i = 0; i < draws.size(); i++){
		for(int j = 0; j < bingocards.size(); j++){
			bingocards[j].crossNumber(draws[i]);
		}
	}
	std::cout << "answer = " << Bingocard::_answer << std::endl;
}