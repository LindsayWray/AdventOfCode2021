#include <iostream>
#include <fstream>
#define FORWARD "forward"
#define DOWN "down"
#define UP "up"


int main(){
	std::string direction;
	int step;
	int horizontal = 0;
	int depth = 0;


	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
	input >> direction;
	input >> step;
	if (direction == FORWARD)
		horizontal += step;
	if (direction == DOWN)
		depth += step;
	if (direction == UP)
		depth -= step;
	}while (!input.eof());
	input.close();

	int answer = horizontal * depth;
	std::cout << answer << std::endl;
}