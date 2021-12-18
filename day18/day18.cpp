#include "Pair.hpp"


Pair	add(Pair pair1, Pair pair2){
	Pair pair(&pair1, &pair2);

	int level = 1;
	
	while(true){
		std::cout << pair.toString() <<std::endl;

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
	return pair;
}

void	addition(std::vector<Pair> pairs){
	int len = pairs.size();

	for (int i = 0; i < len - 1; i++){
		pairs[1] = add(pairs[0], pairs[1]);
		pairs.erase(pairs.begin());
	} 
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