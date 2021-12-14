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

std::map<std::string, long> pairInsert(std::map<std::string, long> pairCount, std::map<std::string, std::string> rules) {
	std::map<std::string, long> newPairCount;
	for(std::map<std::string, long>::iterator it = pairCount.begin(); it != pairCount.end(); it++) {
		newPairCount[it->first] = 0;
	}

	for(std::map<std::string, long>::iterator it = pairCount.begin(); it != pairCount.end(); it++) {
		std::string insert = rules[it->first];
		std::string firstMatch = it->first.substr(0, 1) + insert;
		std::string secondMatch = insert + it->first.substr(1, 1);
		//std::cout << "Split " << it->first << " " << it->second << " times to" << firstMatch << " and " << secondMatch << std::endl; 

		newPairCount[firstMatch] += it->second;
		newPairCount[secondMatch] += it->second;
	}
	return newPairCount;
}

long calculateScore(std::map<std::string, long> pairCount) {
	std::map<char, long> counts;
	// int minimum = polymer.size();
	// int maximum = 0;

	for(std::map<std::string, long>::iterator it = pairCount.begin(); it != pairCount.end(); it++) {
		counts[it->first[0]] = 0;
		counts[it->first[1]] = 0;
	}
	for(std::map<std::string, long>::iterator it = pairCount.begin(); it != pairCount.end(); it++) {
		counts[it->first[0]] += it->second;
		counts[it->first[1]] += it->second;
	}
	long minimum = LONG_MAX;
	long maximum = 0;
	for(std::map<char, long>::iterator it = counts.begin(); it != counts.end(); it++) {
		long count = it->second;
		if (count < minimum)
			minimum = count;
		if (count > maximum)
			maximum = count;
	}
	return (maximum + 1) / 2 - (minimum + 1) / 2;
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

	std::map<std::string, long> pairCount;
	for(std::map<std::string, std::string>::iterator it = rules.begin(); it != rules.end(); it++) {
		pairCount[it->first] = 0;
	}

	for(int i = 1; i < polymer.size(); i++) {
		std::string pair = polymer.substr(i - 1, 2);
		pairCount[pair]++;
	}

	// std::cout << "Starting with" << std::endl;
	// for(std::map<std::string, long>::iterator it = pairCount.begin(); it != pairCount.end(); it++) {
	// 	std::cout << it->first << "," << it->second << std::endl;		
	// }
	// std::cout << "Starting with" << std::endl;

	for (int i = 0; i < 40; i++) {
		pairCount = pairInsert(pairCount, rules);
	}
	long answer = calculateScore(pairCount);
	std::cout << answer << std::endl;

}