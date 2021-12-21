#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>


bool	darkness(int x, int y, std::vector<std::vector<char> > &image){
	if (x < 0 || y < 0 || x > image[0].size() - 1|| y > image.size() - 1)
		return true;
	return false;
}

char	getValue(int x, int y, std::vector<std::vector<char> > &image, std::string algo, int round){	
	std::string binary;
	for(int j = (y - 1); j <= (y + 1); j++){
		for(int i = (x - 1); i <= (x + 1); i++){
			if(darkness(i, j, image))
				binary +=  round % 2 ? '0' : '1';
			else
				binary += image[j][i] == '#' ? '1' : '0';
		}
	}
	return algo[strtol(binary.c_str(), NULL, 2)];
}

std::vector<std::vector<char> >	enhanceImage(std::vector<std::vector<char> > &image, std::string algo, int round){
	std::vector<std::vector<char> > enhanced;

	for(int y = -2; y < (int)image.size() + 2; y++){
		std::vector<char> row;
		for(int x = -2; x < (int)image[0].size() + 2; x++){
			row.push_back(getValue(x, y, image, algo, round));
		}
		enhanced.push_back(row);
	}
	return enhanced;
}

int main(){
	std::string algo;
	std::vector<std::vector<char> > image;
		std::vector<std::vector<char> > enhanced;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	input >> algo;
	do{
		std::string line;
		input >> line;
		std::vector<char> vec; 
		for(int i = 0; i < line.length(); i++)
			vec.push_back(line[i]);
		image.push_back(vec);
	}while(!input.eof());
	// for(int y = 0; y < image.size(); y++){
	// 	for(int x = 0; x < image[0].size(); x++){
	// 		std::cout << image[y][x];
	// 	}
	// 	std::cout << std::endl;
	// }


	enhanced = enhanceImage(image, algo, 1);
	for(int i = 2; i <= 50; i++){
		enhanced = enhanceImage(enhanced, algo, i);
	}
	
	int count = 0;
	for(int y = 0; y < enhanced.size(); y++){
		for(int x = 0; x < enhanced[0].size(); x++){
			//std::cout << enhanced[y][x];
			if(enhanced[y][x] == '#')
				count++;
		}
		//std::cout << std::endl;
	}

	std::cout << count << std::endl;
}