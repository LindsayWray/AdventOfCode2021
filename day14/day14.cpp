#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>

typedef struct rule{
	std::string match;
	char insert;
} fold;

std::string pairInsert(std::string polymer, std::map<std::string, std::string> rules) {
	std::string newString(polymer);

	for(int i = 1; i < polymer.size(); i++) {
		std::string toMatch = polymer.substr(i - 1, 2);
		newString.insert(2 * i - 1, rules[toMatch]);
	}

	return newString;
}

int calculateScore(std::string polymer) {
	std::set<char> chars(polymer.begin(), polymer.end());
	int minimum = polymer.size();
	int maximum = 0;

	for(std::set<char>::iterator it = chars.begin(); it != chars.end(); it++) {
		long long count = std::count(polymer.begin(), polymer.end(), *it);
		if (count < minimum)
			minimum = count;
		if (count > maximum)
			maximum = count;
	}
	return maximum - minimum;
}
 
int main(){
	std::string polymer;
	std::map<std::string, std::string> rules;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	input >> polymer;
		
	do {
		std::string match;
		input >> match;
		std::string replace;
		input >> replace;
		input >> replace;
		rules[match] = replace;
	} while (!input.eof());
	input.close();

	for (int i = 0; i < 10; i++) {
		//std::cout << polymer << std::endl;
		polymer = pairInsert(polymer, rules);
	}

	int answer = calculateScore(polymer);
	std::cout << answer << std::endl;

}