#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef struct octopus{
	int value;
	bool hasFlashed;
} octopus;

octopus	grid [10][10];
int flashCount = 0;

bool	validCoordinate(int x, int y){
	if (x < 0 || y < 0 || x > 9 || y > 9)
		return false;
	return true;
}

void	flash(int y, int x){
	for(int j = (y - 1); j <= (y + 1); j++){
		for(int i = (x - 1); i <= (x + 1); i++){
			if (i == x && j == y)
				continue; //is octopus self
			if(validCoordinate(i, j) && !grid[j][i].hasFlashed){
				grid[j][i].value++;
			}		
		}
	}
	grid[y][x].hasFlashed = true;
	grid[y][x].value = 0;
	flashCount++;
}

void	nextStep(){
	bool aFlashHappened = true;

	for(int y = 0; y < 10; y++){
		for(int x = 0; x < 10; x++)
			grid[y][x].value++;
	}
	while(aFlashHappened){
		aFlashHappened = false;
		for(int y = 0; y < 10; y++){
			for(int x = 0; x < 10; x++){
				if (grid[y][x].value > 9){
					flash(y, x);
					aFlashHappened = true;
				}
			}
		}
	}
	for(int y = 0; y < 10; y++){
		for(int x = 0; x < 10; x++)
			grid[y][x].hasFlashed = false;
	}
}

int main(){

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	for(int j = 0; j < 10; j++){
		std::string line;
		input >> line;
		for(int i = 0; i < line.length(); i++){
			grid[j][i].value = line[i] - 48;
			grid[j][i].hasFlashed = false;
		}
	}
	input.close();

	for(int i = 0; i < 100; i++){
		nextStep();
	}
	std::cout << "answer is: " << flashCount << std::endl;
}