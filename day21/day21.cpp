#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Player 1 starting position: 8
// Player 2 starting position: 5

int main(){
	int player1 = 8;
	int player2 = 5;

	int scorePlayer1 = 0;
	int scorePlayer2 = 0;

	int i = 1;
	while(1){
		player1 += i++;
		player1 += i++;
		player1 += i++;
		player1 %= 10;
		if (player1 == 0)
			player1 = 10;
		if ((scorePlayer1 += player1) >= 1000)
			break;

		player2 += i++;
		player2 += i++;
		player2 += i++;
		player2 %= 10;
		if (player2 == 0)
			player2 = 10;
		// std::cout << player1 << std::endl;
		// std::cout << scorePlayer1 << std::endl;
		if ((scorePlayer2 += player2) >= 1000)
			break;
	}

	std::cout << i << std::endl;
	std::cout << scorePlayer2 << std::endl;
	long answer2 = scorePlayer2 * (i - 1);
	long answer1 = scorePlayer1 * (i - 1);
	std::cout << answer2 << std::endl;
	std::cout << answer1 << std::endl;
}