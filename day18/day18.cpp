#include "Pair.hpp"


Pair	add(Pair *pair1, Pair *pair2){
	Pair pair(pair1, pair2);

	int level = 1;
	
	while(true){
		Pair::leftNeighbour = NULL;
		Pair::rightValueToAdd = -1;
		Pair::explosions = false;

		pair.explode(level);
		if (Pair::explosions) {
			continue;
		}

		if (!pair.split())
			break;
	}
	std::cout << "ADDED " << pair.toString() << std::endl;

	return pair;
}

void	addition(std::vector<Pair> pairs){
	int len = pairs.size();

	Pair total = pairs[0];

	for (int i = 1; i < len; i++){
		std::cout << "adding " << total.toString() << std::endl;
		std::cout << "adding " << pairs[i].toString() << std::endl;

		total = add(&total, &(pairs[i]));
		// pairs.erase(pairs.begin());
	}
	std::cout << "FINAL " << total.toString() << std::endl;
	// std::cout << "ADDED " << pairs[1].toString() << std::endl;
}


int main(){
	std::vector<Pair> pairs;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		std::string line;
		input >> line;
		std::stringstream ss(line);
		Pair pair(ss);
		pairs.push_back(pair);
	}while(!input.eof());
	input.close();

	int len = pairs.size();

	addition(pairs);

	// for (int i = 0; i < len; i++){
	// 	std::cout << pairs[i].toString() <<std::endl;
	// } 


}