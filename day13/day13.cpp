#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


typedef struct coordinate{
	int x;
	int y;
} coordinate;

typedef struct fold{
	char axis;
	int line;
} fold;

int		getMaximumY(std::vector<coordinate> coordinates){
	int max = 0;

	for(int i = 0; i < coordinates.size(); i++){
		if (coordinates[i].y > max)
			max = coordinates[i].y;
	}
	return max;
}

int		getMaximumX(std::vector<coordinate> coordinates){
	int max = 0;

	for(int i = 0; i < coordinates.size(); i++){
		if (coordinates[i].x > max)
			max = coordinates[i].x;
	}
	return max;
}


void	makeGrid(std::vector<coordinate> coordinates, std::vector<fold> folds){
	int maxX = getMaximumX(coordinates) + 1;
	int maxY = getMaximumY(coordinates) + 1;

	int grid[maxY][maxX];

	for(int i = 0; i < maxY; i++){
		for(int j = 0; j < maxX; j++){
			grid[i][j] = 0;
		}
	}

	for(int i = 0; i < coordinates.size(); i++){
		grid[coordinates[i].y][coordinates[i].x] = 1;
	}

	for(int y = 0; y < maxY; y++){
		for(int x = 0; x < maxX; x++){
			if (x > folds[0].line && grid[y][x] == 1){
				int mirrorX = folds[0].line - (x - folds[0].line);
				grid[y][mirrorX] = 1;
				grid[y][x] = 0;
			}
		}
	}

	int count = 0;
	for(int i = 0; i < maxY; i++){
		for(int j = 0; j < maxX; j++){
			if (grid[i][j] == 1)
				count++;
		}
	}
	std::cout << count << std::endl;
}


int main(){
	std::vector<coordinate> coordinates;
	std::vector<fold> folds;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}
	
	std::string line;
	do {
		input >> line;
		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream ss(line);
		coordinate c;
		ss >> c.x;
		ss >> c.y;
		coordinates.push_back(c);
	} while (!input.eof());
	input.close();

	std::ifstream inputFolds("input_folds");
	if (!inputFolds.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do {
		inputFolds >> line;
		std::replace(line.begin(), line.end(), '=', ' ');
		std::stringstream ss(line);
		fold f;
		ss >> f.axis;
		ss >> f.line;
		folds.push_back(f);
	} while (!inputFolds.eof());
	inputFolds.close();

	makeGrid(coordinates, folds);
}