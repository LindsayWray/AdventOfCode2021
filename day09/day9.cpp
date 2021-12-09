#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


int	calculate(std::vector<std::vector<int> > floor){
	int count = 0;

	for (int y = 0; y < floor.size(); y++){
		for (int x = 0; x < floor[y].size(); x++){

			if (x > 0 && floor[y][x] >= floor[y][x - 1])  //left
				continue;
			if (y > 0 && floor[y][x] >= floor[y - 1][x]) //top
				continue;
			if (x < floor[y].size() - 1 && floor[y][x] >= floor[y][x + 1]) //right
				continue;
			if (y < floor.size() - 1 && floor[y][x] >= floor[y + 1][x]) //down
				continue;
			count += floor[y][x] + 1;
		} 
	}

	return count;
}

int main(){
	std::vector<std::vector<int> > floor;
	

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}
	
	for (std::string inputstring; input >> inputstring;){
		std::vector<int> floorline;
		for(int i = 0; i < inputstring.length();i++){
			floorline.push_back(inputstring[i] - 48);
		}
		floor.push_back(floorline);
	}

	int answer = calculate(floor);
	std::cout << "answer is: " << answer << std::endl;

}