#include "Pair.hpp"


Pair*	add(Pair* pair1, Pair* pair2){
	Pair* pair = new Pair(pair1, pair2);

	int level = 1;
	
	while(true){
		Pair::leftNeighbour = NULL;
		Pair::rightValueToAdd = -1;
		Pair::explosions = false;

		pair->explode(level);
		if (Pair::explosions) {
			continue;
		}

		if (!pair->split())
			break;
	}

	return pair;
}


long	find_max(std::vector<Pair*> pairs){
	long max = 0;

	for (int i = 0; i < pairs.size(); i++){
		for (int j = 0; j < pairs.size(); j++){
			if (i == j)
				continue;
			long ans1 = add(pairs[i], pairs[j])->magitude();
			if (ans1 > max)
			{
				max = ans1;
				std::cout << i << "," << j << std::endl;
			}
			long ans2 = add(pairs[j], pairs[i])->magitude();
			if (ans2 > max)
				std::cout << i << "," << j << std::endl;
				max = ans2;
		}
	}
	return max;
}


int main(){
	std::vector<Pair*> pairs;

	std::ifstream input("../input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		std::string line;
		input >> line;
		std::stringstream ss(line);
		Pair* pair = new Pair(ss);
		pairs.push_back(pair);
	}while(!input.eof());
	input.close();

	int len = pairs.size();

	std::cout << find_max(pairs) << std::endl;

	// for (int i = 0; i < len; i++){
	// 	std::cout << pairs[i].toString() <<std::endl;
	// } 


}