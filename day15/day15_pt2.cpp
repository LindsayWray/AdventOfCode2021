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


typedef struct element{

} element;

coordinate		findSmallest(std::vector<std::vector<node> > &grid, std::vector<coordinate> &list){
	int minValue = INT_MAX;
	coordinate smallest;
	int indexToRemove;


	for(int i = 0; i < list.size(); i++){
		int x = list[i].x;
		int y = list[i].y;
		if (grid[y][x].totalRisk < minValue){
			smallest.x = x;
			smallest.y = y;
			minValue = grid[y][x].totalRisk;
			indexToRemove = i;
		}

	}
	list.erase(list.begin() + indexToRemove);
	return smallest;
}

void	compareValues(node current, node &neighbour){
	if (current.totalRisk + neighbour.riskLevel < neighbour.totalRisk)
		neighbour.totalRisk = current.totalRisk + neighbour.riskLevel;
	

}

void addToList(int x, int y, std::vector<coordinate> &list) {
	for(int i = 0; i < list.size(); i++){
		if (list[i].x == x && list[i].y == y)
			return;
	}
	coordinate nb = { x, y };
	list.push_back(nb);
}

void	updateNeighbours(std::vector<std::vector<node> > &grid, coordinate smallest, std::vector<coordinate> &list){
	if (smallest.y > 0 && !grid[smallest.y - 1][smallest.x].marked)	{					//check top neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y - 1][smallest.x]);
		addToList(smallest.x, smallest.y - 1, list);
	}
	if (smallest.y < grid.size() - 1 && !grid[smallest.y + 1][smallest.x].marked) {		//check below neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y + 1][smallest.x]);
		addToList(smallest.x, smallest.y + 1, list);
	}
	if (smallest.x > 0 && !grid[smallest.y][smallest.x - 1].marked)	{					//check left neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y][smallest.x - 1]);
		addToList(smallest.x - 1, smallest.y, list);
	}
	if (smallest.x < grid[0].size() - 1 && !grid[smallest.y][smallest.x + 1].marked) {	//check right neighbour
		compareValues(grid[smallest.y][smallest.x], grid[smallest.y][smallest.x + 1]);
		addToList(smallest.x + 1, smallest.y, list);
	}
}


int		findSafestRoute(std::vector<std::vector<node> > &grid){
	grid[0][0].totalRisk = 0;
	std::vector<coordinate> list;
	coordinate start = { 0, 0 };
	list.push_back(start);
	
	while(!grid[grid.size() - 1][grid[0].size() - 1].marked){  // while bottom right is not marked
		coordinate smallest = findSmallest(grid, list);
		updateNeighbours(grid, smallest, list);
		grid[smallest.y][smallest.x].marked = true;
	}

	return grid[grid.size() - 1][grid[0].size() - 1].totalRisk;
}

int main(){
std::vector<std::vector<node> > basicGrid;
std::vector<std::vector<node> > arrayOfGrids[5][5];

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
		basicGrid.push_back(row);

	}while (!input.eof());
	input.close();

	std::vector<std::vector<node> > bigGrid;

	for(int i = 0; i < 5 * basicGrid.size(); i++) {
		std::vector<node> bigRow;
		for(int j = 0; j < 5; j++){
				for(int k = 0; k < basicGrid[0].size(); k++){
					node nextNumber;
					nextNumber.riskLevel = basicGrid[i % basicGrid.size()][k].riskLevel;
					nextNumber.riskLevel += (i / basicGrid.size()) + j;
					if (nextNumber.riskLevel > 9)
						nextNumber.riskLevel %= 9;
					nextNumber.totalRisk = INT_MAX;
					nextNumber.marked = false;
					bigRow.push_back(nextNumber);
				}
		}
		bigGrid.push_back(bigRow);
	}

	std::ofstream output("big_grid");

	for(int i = 0; i < bigGrid.size(); i++){
		for(int j = 0; j < bigGrid[0].size(); j++){
			output << bigGrid[i][j].riskLevel;
		}
		output << std::endl;
	}

	int answer = findSafestRoute(bigGrid);
	std::cout << answer << std::endl;
}