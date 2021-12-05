#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

typedef struct line{
	int startX;
	int startY;
	int endX;
	int endY;
} line;

void	drawLines(std::vector<line> lines){
	int grid [1000][1000];

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			grid[i][j] = 0;
		}
	}

	for(int i = 0; i < lines.size(); i++) {
		line l = lines[i];
		if (l.startX == l.endX) {
			if (l.endY > l.startY) {
				for (int y = l.startY; y <= l.endY; y++) {
					grid[l.startX][y]++;
				}
			} else {
				for (int y = l.startY; y >= l.endY; y--) {
					grid[l.startX][y]++;
				}
			}
			continue;
		}
		if (l.startY == l.endY) {
			if (l.endX > l.startX) {
				for (int x = l.startX; x <= l.endX; x++) {
					grid[x][l.startY]++;
				}
			} else {
				for (int x = l.startX; x >= l.endX; x--) {
					grid[x][l.startY]++;
				}
			}
		}
		int slope = (l.endY - l.startY) / (l.endX - l.startX);
		if (slope == 1 && l.startX < l.endX) {
			for (int x = l.startX, y = l.startY; x <= l.endX; x++, y++) {
					grid[x][y]++;
			}
		}
		if (slope == 1 && l.startX > l.endX) {
			for (int x = l.startX, y = l.startY; x >= l.endX; x--, y--) {
					grid[x][y]++;
			}
		}
		if (slope == -1 && l.startX < l.endX) {
			for (int x = l.startX, y = l.startY; x <= l.endX; x++, y--) {
					grid[x][y]++;
			}
		}
		if (slope == -1 && l.startX > l.endX) {
			for (int x = l.startX, y = l.startY; x >= l.endX; x--, y++) {
					grid[x][y]++;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (grid[i][j] > 1) {
				count++;
			}
		}
	}
	std::cout << "Count = " << count << std::endl;
}

int main(){
	std::vector<line> lines;
	

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do {
		line l;
		input >> l.startX;
		if (input.peek() == ',')
			input.ignore();
		input >> l.startY;
		std::string arrow;
		input >> arrow;
		input >> l.endX;
		if (input.peek() == ',')
			input.ignore();
		input >> l.endY;
		lines.push_back(l);
	} while (!input.eof());
	input.close();

	std::cout << lines.size() << std::endl;
	drawLines(lines);
	std::cout << lines[8].startX << lines[8].startY << lines[8].endX << lines[8].endY << std::endl;
}