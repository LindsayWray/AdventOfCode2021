#include "Bingocard.hpp"

Bingocard::Bingocard(int grid[25]) : _done(false) {
	for(int i = 0; i < 25; i++){
		_card[i/5][i%5] = grid[i]; 
	}
}

void Bingocard::crossNumber(int num){
	for(int i = 0; i < 25; i++){
		if (_card[i/5][i%5] == num){
			_card[i/5][i%5] = -1;
			if(checkForWin())
				calculateAnswer(num);
		}
	}

}

bool Bingocard::checkForWin(){
	for(int i = 0; i < 5; i++){
		bool horizontalWin = true;
		for(int j = 0; j < 5; j++){
			if(_card[i][j] != -1){
				horizontalWin = false;
				break;
			}
		}
		if (horizontalWin)
			return true;
	}

	for(int i = 0; i < 5; i++){
		bool verticalWin = true;
		for(int j = 0; j < 5; j++){
			if(_card[j][i] != -1){
				verticalWin = false;
				break;
			}
		}
		if (verticalWin)
			return true;
	}
	return false;
}

void Bingocard::calculateAnswer(int num){

	if (!_done){
		long answer = 0;
		for(int i = 0; i < 25; i++){
			if (_card[i/5][i%5] != -1)
				answer += _card[i/5][i%5];
		}
		answer *= num;
		std::cout << "answer = " << answer << std::endl;
		_done = true;
	}
}
