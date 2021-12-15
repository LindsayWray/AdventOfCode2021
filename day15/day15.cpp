#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>

// 1. find smallest unmarked 
// 2. update it's neighbours if smaller
// 3. mark it

typedef struct node{
	int riskLevel;
	int totalRisk;
	bool marked;
} node;

typedef struct coordinate{
	int x;
	int y;
} coordinate;


coordinate		findSmallest(std::vector<std::vector<node> > &grid){
	int minValue = INT_MAX;
	coordinate smallest;

	for(int y = 0; y < grid.size(); y++){
		for(int x = 0; x < grid[0].size(); x++){
			if (!grid[y][x].marked && grid[y][x].totalRisk < minValue){
				smallest.x = x;
				smallest.y = y;
				minValue = grid[y][x].totalRisk;
			}
		}
	}
	return smallest;
}

void	compareValues(node current, node &neighbour){
	if (current.totalRisk + neighbour.riskLevel < neighbour.totalRisk)
		neighbour.totalRisk = current.totalRisk + neighbour.riskLevel;
}


void	updateNeighbours(std::vector<std::vector<node> > &grid, coordinate smallest){
	if (smallest.y > 0 && !grid[smallest.y - 1][smallest.x].marked)						//check top neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y - 1][smallest.x]);
	if (smallest.y < grid.size() - 1 && !grid[smallest.y + 1][smallest.x].marked)		//check below neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y + 1][smallest.x]);
	if (smallest.x > 0 && !grid[smallest.y][smallest.x - 1].marked)						//check left neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y][smallest.x - 1]);
	if (smallest.x < grid[0].size() - 1 && !grid[smallest.y][smallest.x + 1].marked)	//check right neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y][smallest.x + 1]);
}


int		findSafestRoute(std::vector<std::vector<node> > &grid){
	grid[0][0].totalRisk = 0;

	while(!grid[grid.size() - 1][grid[0].size() - 1].marked){  // while bottom right is not marked
		coordinate smallest = findSmallest(grid);
		updateNeighbours(grid, smallest);
		grid[smallest.y][smallest.x].marked = true;
	}

	return grid[grid.size() - 1][grid[0].size() - 1].totalRisk;
}

int main(){
std::vector<std::vector<node> > grid;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do {
		std::vector<node> row;
		std::string line;
		input >> line;
		for (int i = 0; i < line.length(); i++){
			node n;
			n.riskLevel = line[i] - 48;
			n.totalRisk = INT_MAX;
			n.marked = false;
			row.push_back(n);
		}
		grid.push_back(row);

	}while (!input.eof());
	input.close();

	int answer = findSafestRoute(grid);
	std::cout << answer << std::endl;
}