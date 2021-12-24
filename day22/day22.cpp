#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>

typedef struct cuboid{
	int minX, maxX, minY, maxY, minZ, maxZ;
	bool state;
} cuboid;


long	countState(std::list<cuboid> cuboids){
	long onCounter = 0;

	for(int z = -50; z <= 50; z++){
		for(int y = -50; y <= 50; y++){
			for(int x = -50; x <= 50; x++){
				for(std::list<cuboid>::iterator it = cuboids.begin(); it != cuboids.end(); it++){
					if(x >= it->minX && x <= it-> maxX && y >= it->minY && y <= it-> maxY && z >= it->minZ && z <= it-> maxZ){
						if (it->state)
							onCounter++;
						break;
					}
				}
			}
		}
	}
	return onCounter;
}

int main(){
	std::list<cuboid> cuboids;
	
	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	do{
		cuboid c;
		std::string state;
		input >> state;
		c.state = state == "on" ? true : false;
		std::string coordinates;
		input >> coordinates;
		std::stringstream ss(coordinates);
		ss.ignore(2);
		ss >> c.minX;
		ss.ignore(2);
		ss >> c.maxX;
		ss.ignore(3);
		ss >> c.minY;
		ss.ignore(2);
		ss >> c.maxY;
		ss.ignore(3);
		ss >> c.minZ;
		ss.ignore(2);
		ss >> c.maxZ;
		if (c.minX < -50 || c.maxX > 50 || c.minY < -50 || c.maxY > 50 || c.minZ < -50 || c.maxZ > 50)
			continue;
		cuboids.push_front(c);
	}while(!input.eof());

	// for(std::list<cuboid>::iterator it = cuboids.begin(); it != cuboids.end(); it++){
	// 	std::cout << it->state << "  " << it->minX << " " << it->maxX << "  " << it->minY << " " << it->maxY << "  " << it->minZ << " " << it->maxZ << std::endl; 
	// }

	long answer = countState(cuboids);

	std::cout << answer << std::endl;

}