#include <iostream>
#include <fstream>
#define FORWARD "forward"
#define DOWN "down"
#define UP "up"


int main(){
	std::string direction;
	int step;
	long horizontal = 0;
	long depth = 0;
	long aim = 0;


	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		input >> direction;
		input >> step;
		if (direction == FORWARD){
			horizontal += step;
			depth += (aim * step);
		}
		if (direction == DOWN)
			aim += step;
		if (direction == UP)
			aim -= step;
	} while (!input.eof());
	input.close();

	long answer = horizontal * depth;
	std::cout << answer << std::endl;
}