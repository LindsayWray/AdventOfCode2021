#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <deque>

typedef struct move {
	int from;
	int to;
} move;

std::deque<move> answer;

void printHallway(std::vector<std::deque<char> > &hallway) {	
	for(int i = 0; i < 11; i++){
		if (i == 2 || i == 4 || i == 6 || i == 8)
			std::cout << "-";
		for (int j = 0; j < hallway[i].size(); j++) {
			std::cout << hallway[i][j];
		}
		std::cout << std::endl;
	}
}

bool contains(std::deque<char> deq, char toFind) {
	if (std::find(deq.begin(), deq.end(), toFind) != deq.end())
		return true;
	return false;
}

bool moveAllowed(std::vector<std::deque<char> > &hallway, int from, int to) {
	char charToMove = hallway[from].front();
	if (to == 2) {
		if (charToMove != 'A')
			return false;
		if (contains(hallway[to], 'B') || contains(hallway[to], 'C') || contains(hallway[to], 'D')) {
			return false;
		}
	}
	else if (to == 4) {
		if (charToMove != 'B')
			return false;
		if (contains(hallway[to], 'A') || contains(hallway[to], 'C') || contains(hallway[to], 'D')) {
			return false;
		}
	}
	else if (to == 6) {
		if (charToMove != 'C')
			return false;
		if (contains(hallway[to], 'A') || contains(hallway[to], 'B') || contains(hallway[to], 'D')) {
			return false;
		}
	}
	else if (to == 8) {
		if (charToMove != 'D')
			return false;
		if (contains(hallway[to], 'A') || contains(hallway[to], 'B') || contains(hallway[to], 'C')) {
			return false;
		}
	}
	else { // main hallway spot
		if (!hallway[to].empty())
			return false;
		if (from != 2 && from != 4 && from != 6 && from != 8) { //from hallway to hallway not allowed
			return false;
		}
		else {
			if (from == 2 && !contains(hallway[from], 'B') && !contains(hallway[from], 'C') && !contains(hallway[from], 'D'))
				return false; //do not move an A from the correct stack if there are only A's
			if (from == 4 && !contains(hallway[from], 'A') && !contains(hallway[from], 'C') && !contains(hallway[from], 'D'))
				return false; 
			if (from == 6 && !contains(hallway[from], 'A') && !contains(hallway[from], 'B') && !contains(hallway[from], 'D'))
				return false;
			if (from == 8 && !contains(hallway[from], 'A') && !contains(hallway[from], 'B') && !contains(hallway[from], 'C'))
				return false;
		}
	}
	// Check if no one is in the way
	if (to < from) {
		for (int i = to + 1; i < from; i ++) {
			if (i != 2 && i != 4 && i != 6 && i != 8 && !hallway[i].empty()) {
				return false;
			}
		}
	}
	else {
		for (int i = from + 1; i < to; i ++) {
			if (i != 2 && i != 4 && i != 6 && i != 8 && !hallway[i].empty())
				return false;
		}
	}
	return true;
}

bool checkWin(std::vector<std::deque<char> > &hallway, std::deque<move> &moves) {

	if (hallway[2].size() == 4 && hallway[2].front() == 'A' 
		&& hallway[4].size() == 4 && hallway[4].front() == 'B'
		&& hallway[6].size() == 4 && hallway[6].front() == 'C'
		&& hallway[8].size() == 4 && hallway[8].front() == 'D') {
			std::cout << "we won in " << moves.size() << " steps !" << std::endl;
			if (answer.empty() || answer.size() > moves.size())
				answer = moves;
			return true;
			// for (int j = 0; j < moves.size(); j++) {
			// 	std::cout << moves[j].from << " -> " << moves[j].to << std::endl;
			// }
			//return;

	}
	return false;
}

void makeMove(std::vector<std::deque<char> > &hallway, std::deque<move> &moves) {
	if (checkWin(hallway, moves))
		return;

	// if (moves.size() < 3) {
	// 	for (int j = 0; j < moves.size(); j++) {
	// 		std::cout << moves[j].from << " -> " << moves[j].to << std::endl;
	// 	}
	// 	std::cout << "-----" << std::endl;
	// }

	// if (moves.size() > 22) {
	// 	std::cout << "almost there?" << std::endl;
	// 	for (int i = 0; i < moves.size(); i++) {
	// 		std::cout << moves[i].from << " -> " << moves[i].to << std::endl;
	// 	}
	// 	printHallway(hallway);
	// 	std::cout << "-----" << std::endl;
	// }

	//std::cout << moves.size() << std::endl;

	for(int i = 0; i < 11; i++){
		if (!hallway[i].empty()) {
			for(int j = 0; j < 11; j++){
				if (i == j)
					continue;
				if (!moves.empty() && moves.back().from == j && moves.back().to == i) // just made the opposite move
					continue;
				if (moveAllowed(hallway, i, j)) {
					hallway[j].push_front(hallway[i].front());
					hallway[i].pop_front();
					move m;
					m.from = i;
					m.to = j;
					moves.push_back(m);
					// for (int j = 0; j < moves.size(); j++) {
					// 	std::cout << moves[j].from << " -> " << moves[j].to << std::endl;
					// }
					// std::cout << "-----" << std::endl;
					// printHallway(hallway);
					makeMove(hallway, moves);
					// checkWin(hallway, moves);
					//revert after trying
					hallway[i].push_front(hallway[j].front());
					hallway[j].pop_front();
					if (!moves.empty())
						moves.pop_back();
				}
			}
		}
	}
	// if (!moves.empty())
	// 	moves.pop_back();
}

int main(){
	std::vector<std::deque<char> > hallway;

	for(int i = 0; i < 11; i++){
		std::deque<char> stack;
		hallway.push_back(stack);
	}

	// ACTUAL INPUT
	hallway[2].push_front('C');
	hallway[2].push_front('D');
	hallway[2].push_front('D');
	hallway[2].push_front('A');

	hallway[4].push_front('D');
	hallway[4].push_front('B');
	hallway[4].push_front('C');
	hallway[4].push_front('D');

	hallway[6].push_front('B');
	hallway[6].push_front('A');
	hallway[6].push_front('B');
	hallway[6].push_front('C');

	hallway[8].push_front('B');
	hallway[8].push_front('C');
	hallway[8].push_front('A');
	hallway[8].push_front('A');

	//EXAMPLE INPUT
	// hallway[2].push_front('A');
	// hallway[2].push_front('D');
	// hallway[2].push_front('D');
	// hallway[2].push_front('B');

	// hallway[4].push_front('D');
	// hallway[4].push_front('B');
	// hallway[4].push_front('C');
	// hallway[4].push_front('C');

	// hallway[6].push_front('C');
	// hallway[6].push_front('A');
	// hallway[6].push_front('B');
	// hallway[6].push_front('B');

	// hallway[8].push_front('A');
	// hallway[8].push_front('C');
	// hallway[8].push_front('A');
	// hallway[8].push_front('D');

	std::deque<move> moves;

	makeMove(hallway, moves);

	for (int j = 0; j < answer.size(); j++) {
		std::cout << answer[j].from << " -> " << answer[j].to << std::endl;
	}
}