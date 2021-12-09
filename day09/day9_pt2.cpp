#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


int	findBasin(std::vector<std::vector<int> > &floor, int y, int x){
	int size = 0;

	if (x > 0 && floor[y][x - 1] != 9 && floor[y][x - 1] != -1){					//left
		floor[y][x - 1] = -1;
		size++;
		size += findBasin(floor, y, x -1);
	}
	if (y > 0 && floor[y - 1][x] != 9 && floor[y - 1][x] != -1){					//top
		floor[y - 1][x] = -1;
		size++;
		size += findBasin(floor, y - 1, x);
	}
	if (x < floor[y].size() - 1 && floor[y][x + 1] != 9 && floor[y][x + 1] != -1){	//right
		floor[y][x + 1] = -1;
		size++;
		size += findBasin(floor, y, x + 1);
	}
	if (y < floor.size() - 1 && floor[y + 1][x] != 9 && floor[y + 1][x] != -1){		//down
		floor[y + 1][x] = -1;
		size++;
		size += findBasin(floor, y + 1, x);
	}
	return size;
}


std::vector<int>	calculate(std::vector<std::vector<int> > floor){
	std::vector<int> sizes;
	int count = 0;

	for (int y = 0; y < floor.size(); y++){
		for (int x = 0; x < floor[y].size(); x++){

			if (x > 0 && floor[y][x] >= floor[y][x - 1])				//left
				continue;
			if (y > 0 && floor[y][x] >= floor[y - 1][x])				//top
				continue;
			if (x < floor[y].size() && floor[y][x] >= floor[y][x + 1])	//right
				continue;
			if (y < floor.size() - 1 && floor[y][x] >= floor[y + 1][x])	//down
				continue;
			sizes.push_back(findBasin(floor, y, x));

		} 
	}
	return sizes;
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

	std::vector<int> sizes = calculate(floor);

	std::sort(sizes.rbegin(), sizes.rend());
	int answer = sizes[0] * sizes[1] * sizes[2];
	std::cout << "answer is: " << answer << std::endl;
}