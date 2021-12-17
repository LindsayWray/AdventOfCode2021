#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


bool	calculateTrajectory(int xSpeed, int ySpeed){
	int x = 0;
	int y = 0;

	while(x <= 65 && y >= -225){
		x += xSpeed;
		if (xSpeed > 0)
			xSpeed--;
		y += ySpeed;
		ySpeed--;
		if (x >= 32 && x <= 65 && y <= -177 && y >= -225)
			return true;
	}
	return false;
}

int main(){
	int count = 0;

	for (int i = 8; i <= 65; i++){
		for(int j = -225; j <= 224; j++){
			if (calculateTrajectory(i, j))
				count++;
		}
	}

	std::cout << count << std::endl;
}