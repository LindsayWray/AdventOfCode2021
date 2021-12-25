#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int cucumbersMove(std::vector<std::vector<char> > floor){
	int count = 0;
	std::vector<std::vector<char> > east;
	int width = floor[0].size();
	int height = floor.size();

	for(int i = 0; i < height; i++){
		std::vector<char> v;
		for(int j = 0; j < width; j++){
			v.push_back('0');
		}
		east.push_back(v);
	}

	bool canMove = true;
	while(canMove){
		canMove = false;
		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				if(floor[y][x] == '>' && floor[y][(x + 1) % width] == '.'){
					east[y][(x + 1) % width] = '>';
					east[y][x] = '.';
					canMove = true;
				}
				else if(!(floor[y][(x - 1 + width) % width] == '>' && floor[y][x] == '.'))
					east[y][x] = floor[y][x];
			}
		}

		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				if(east[y][x] == 'v' && east[(y + 1) % height][x] == '.'){
					floor[(y + 1) % height][x] = 'v';
					floor[y][x] = '.';
					canMove = true;
				}
				else if(!(east[(y - 1 + height) % height][x] == 'v' && east[y][x] == '.'))
					floor[y][x] = east[y][x];
			}
		}
		count++;
	}
	return count;
}


int main(){
	std::vector<std::vector<char> > floor;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		std::string line;
		input >> line;
		std::vector<char> v;
		for(int i = 0; i < line.length(); i++)
			v.push_back(line[i]);
		floor.push_back(v);
	}while(!input.eof());

	int answer = cucumbersMove(floor);
	std::cout << "answer: " << answer << std::endl;
}