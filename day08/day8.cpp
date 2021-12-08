 #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

typedef struct lines{
	std::vector<std::string> digits;
	std::vector<std::string> output;
} lines;


void sortString(std::string &str)
{
   std::sort(str.begin(), str.end());
}


bool	containsAll(std::string str1, std::string str2){
	for(int i = 0; i < str1.length(); i++){
		if (str2.find(str1[i])  == std::string::npos)
			return false;
	}
	return true;
}

int		decode(lines line){
	std::string mapping[10];
	for (int i = 0; i < 10; i++){
		if (line.digits[i].length() == 2)
			mapping[1] = line.digits[i];
	}
	for (int i = 0; i < 10; i++){
		if (line.digits[i].length() == 3)
			mapping[7] = line.digits[i];
	}
	for (int i = 0; i < 10; i++){
		if (line.digits[i].length() == 4)
			mapping[4] = line.digits[i];
	}
	for (int i = 0; i < 10; i++){
		if (line.digits[i].length() == 7)
			mapping[8] = line.digits[i];
	}
	for (int i = 0; i < 10; i++){
		if (line.digits[i].length() == 6){
			if (containsAll(mapping[4], line.digits[i]))
				mapping[9] = line.digits[i];
			else if (containsAll(mapping[1], line.digits[i]))
				mapping[0] = line.digits[i];
			else
				mapping[6] = line.digits[i];
		}	
	}
	for (int i = 0; i < 10; i++){
		if (line.digits[i].length() == 5){
			if (containsAll(mapping[7], line.digits[i]))
				mapping[3] = line.digits[i];
			else if (containsAll(line.digits[i], mapping[6]))
				mapping[5] = line.digits[i];
			else
				mapping[2] = line.digits[i];
		}	
	}

	int output = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 10; j++){
			if (line.output[i] == mapping[j])
				output = (output * 10) + j;
		}
	}
	return output;
}

int main(){
	std::vector<lines> entries;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	std::string delimiter;
	do{
		lines entry;
		for(int i = 0; i < 10; i++){
			std::string str;
			input >> str;
			sortString(str);
			entry.digits.push_back(str);
		}
		input >> delimiter;
		for(int i = 0; i < 4; i++){
			std::string str;
			input >> str;
			sortString(str);
			entry.output.push_back(str);
		}
		entries.push_back(entry);
	}  while (!input.eof());
	input.close();


	long long count = 0;
	for (int i  = 0; i < entries.size(); i++){
		count += decode(entries[i]);
	}

	// for (int i  = 0; i < entries.size(); i++){
	// 	for (int j = 0; j < 4; j++){
	// 		int len = entries[i].output[j].length();
	// 		if (len == 2 || len == 3 || len == 4 || len == 7)
	// 			count++;
	// 	}
	// }

	std::cout << "answer is: " << count << std::endl;
}