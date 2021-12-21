#include <iostream>
#include <fstream>
#include <string>
#include <map>

// Player 1 starting position: 8
// Player 2 starting position: 5

typedef struct universe{
	int player1;
	int player2;
	int scorePlayer1;
	int scorePlayer2;
} universe;

bool operator<(const universe& lhs, const universe& rhs)
{
	return (lhs.player1 < rhs.player1) ||
	(lhs.player1 == rhs.player1 && lhs.player2 < rhs.player2) ||
	(lhs.player1 == rhs.player1 && lhs.player2 == rhs.player2 && lhs.scorePlayer1 < rhs.scorePlayer1) ||
	(lhs.player1 == rhs.player1 && lhs.player2 == rhs.player2 && lhs.scorePlayer1 == rhs.scorePlayer1 && lhs.scorePlayer2 < rhs.scorePlayer2);
}

bool someoneHasWon(universe u) {
	if (u.scorePlayer1 >= 21)
		return true;
	if (u.scorePlayer2 >= 21)
		return true;
	return false;
}

void updateMap(std::map<universe, long> &newCounter, universe u, long count) {
	if (newCounter.find(u) == newCounter.end())	
		newCounter.insert(std::pair<universe, long>(u, count));
	else
		newCounter[u] += count;
}

std::map<universe, long> rollPlayer1(std::map<universe, long> previousCounter) {
	std::map<universe, long> newCounter;

	for(std::map<universe, long>::iterator it=previousCounter.begin(); it!=previousCounter.end(); it++) {
		universe u = it->first;
		if (someoneHasWon(u)) {
			newCounter.insert(std::pair<universe, long>(u, it->second));
			continue;
		}
		for (int i = 0; i < 3; i++) {
			u.player1++;
			u.player1 %= 10;
			if (u.player1 == 0)
				u.player1 = 10;		
			updateMap(newCounter, u, it->second);
		}		
	}
	return newCounter;
}

std::map<universe, long> rollPlayer2(std::map<universe, long> previousCounter) {
	std::map<universe, long> newCounter;

	for(std::map<universe, long>::iterator it=previousCounter.begin(); it!=previousCounter.end(); it++) {
		universe u = it->first;
		if (someoneHasWon(u)) {
			newCounter.insert(std::pair<universe, long>(u, it->second));
			continue;
		}
		for (int i = 0; i < 3; i++) {
			u.player2++;
			u.player2 %= 10;
			if (u.player2 == 0)
				u.player2 = 10;		
			updateMap(newCounter, u, it->second);
		}
	}
	return newCounter;
}

std::map<universe, long> scorePlayer1(std::map<universe, long> previousCounter) {
	std::map<universe, long> newCounter;

	for(std::map<universe, long>::iterator it=previousCounter.begin(); it!=previousCounter.end(); it++) {
		universe u = it->first;
		if (someoneHasWon(u)) {
			updateMap(newCounter, u, it->second);
			continue;
		}
		u.scorePlayer1 += u.player1;
		updateMap(newCounter, u, it->second);
	}
	return newCounter;
}

std::map<universe, long> scorePlayer2(std::map<universe, long> previousCounter) {
	std::map<universe, long> newCounter;

	for(std::map<universe, long>::iterator it=previousCounter.begin(); it!=previousCounter.end(); it++) {
		universe u = it->first;
		if (someoneHasWon(u)) {
			updateMap(newCounter, u, it->second);
			continue;
		}
		u.scorePlayer2 += u.player2;
		updateMap(newCounter, u, it->second);
	}
	return newCounter;
}

int main(){
	std::map<universe, long> universecounter;

	universe start;
	start.player1 = 8;
	start.player2 = 5;
	start.scorePlayer1 = 0;
	start.scorePlayer2 = 0;
	universecounter.insert(std::pair<universe, long>(start, 1));


	// for(std::map<universe, int>::iterator it=universecounter.begin(); it!=universecounter.end(); it++) {
	// 	std::cout << "Universe p1 " << it->first.player1 << ", p2 " <<  it->first.player2 << ", count " << it->second << std::endl;
	// }

	for(int i = 0; i < 21; i++){
		universecounter = rollPlayer1(universecounter);
		universecounter = rollPlayer1(universecounter);
		universecounter = rollPlayer1(universecounter);

		universecounter = scorePlayer1(universecounter);

		universecounter = rollPlayer2(universecounter);
		universecounter = rollPlayer2(universecounter);
		universecounter = rollPlayer2(universecounter);

		universecounter = scorePlayer2(universecounter);
	}

	long long winsPlayer1 = 0;
	long long winsPlayer2 = 0;
	for(std::map<universe, long>::iterator it=universecounter.begin(); it!=universecounter.end(); it++) {
		if (it->first.scorePlayer1 >= 21)
			winsPlayer1 += it->second;
		else
			winsPlayer2 += it->second;
	}

	std::cout << winsPlayer1 << std::endl;
	std::cout << winsPlayer2 << std::endl;
}