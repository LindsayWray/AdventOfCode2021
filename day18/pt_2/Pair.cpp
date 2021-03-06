#include "Pair.hpp"

int * Pair::leftNeighbour = NULL;
int Pair::rightValueToAdd = -1;
bool Pair::explosions = false;

Pair::Pair(std::stringstream &ss){
	ss.ignore(); //ignores opening bracket

	if (ss.peek() == '[')
		_left = new Pair(ss);
	else{
		ss >> _leftNum;
		_left = NULL;
	}

	ss.ignore(); //ignores comma

	if (ss.peek() == '[')
		_right = new Pair(ss);
	else{
		ss >> _rightNum;
		_right = NULL;
	}

	ss.ignore(); //ignores closing bracket
}

Pair::Pair(Pair *pair1, Pair *pair2) {
	 _left = new Pair(*pair1);
	 _right= new Pair(*pair2);
}

Pair::Pair(int left, int right) : _leftNum(left), _rightNum(right), _left(NULL), _right(NULL) {}

std::string Pair::toString() {
	std::stringstream str;
	str << "[";
	if (_left)
		str << _left->toString();
	else 
		str << _leftNum;
	str << ",";
	if (_right)
		str << _right->toString();
	else 
		str << _rightNum;

	str << "]";
	return str.str();
}

bool	Pair::split(){
	if(_left) {
		if (_left->split())
			return true;
	}
	else {
		if (_leftNum >= 10) {
			_left = new Pair(_leftNum / 2, (_leftNum + 1) / 2);
			_leftNum = 0;
			return true;
		}
	}
	if(_right) {
		if (_right->split())
			return true;
	}
	else {
		if (_rightNum >= 10) {
			_right = new Pair(_rightNum / 2, (_rightNum + 1) / 2);
			_rightNum = 0;
			return true;
		}
	}
	return false;
}

bool	Pair::explode(int level){
	if(level == 4 && _left && !explosions) {
		// std::cout << "Exploding L " << _left->toString() << std::endl;
		Pair::explosions = true;
		if (leftNeighbour)
			*leftNeighbour += _left->_leftNum;
		rightValueToAdd = _left->_rightNum;
		_left = NULL;
		_leftNum = 0;
	}
	else if (_left) {
		_left->explode(level + 1);
	}
	else {
		if (rightValueToAdd != -1) {
			_leftNum += rightValueToAdd;
			rightValueToAdd = -1;
		}
		leftNeighbour = &_leftNum;
	}

	if(level == 4 && _right && !explosions) {
		// std::cout << "Exploding R " << _right->toString() << std::endl;
		Pair::explosions = true;
		if (leftNeighbour)
			*leftNeighbour += _right->_leftNum;
		rightValueToAdd = _right->_rightNum;
		_right = NULL;
		_rightNum = 0;
	}
	else if (_right) {
		_right->explode(level + 1);
	}
	else {
		if (rightValueToAdd != -1) {
			_rightNum += rightValueToAdd;
			rightValueToAdd = -1;
		}
		leftNeighbour = &_rightNum;
	}
	return false;
}

long Pair::magitude() {
	long mag = 0;
	if (_left)
		mag += 3 *_left->magitude();
	else 
		mag += 3 * _leftNum;
	if (_right)
		mag += 2 * _right->magitude();
	else 
		mag += 2 *_rightNum;
	return mag;
}

	// if(level < 4){		
	// 	if(_left) {
	// 	 	if (_left->explode(level + 1)){
	// 			exploded = true;			
	// 			if (!_right && rightValueToAdd != -1) {			
	// 				_rightNum += rightValueToAdd;
	// 				rightValueToAdd = -1;
	// 			}
	// 		}
	// 	}
	// 	else {
	// 		if (rightValueToAdd != -1) {
	// 			_leftNum += rightValueToAdd;
	// 			rightValueToAdd = -1;
	// 		}
	// 		leftNeighbour = &_leftNum;
	// 	}

	// 	if(_right) {
	// 		if (_right->explode(level + 1)){
	// 			exploded = true;
	// 			return rightValueToAdd == -1;
	// 		}
	// 	}
	// 	else {
	// 		if (rightValueToAdd != -1) {			
	// 			_rightNum += rightValueToAdd;
	// 			rightValueToAdd = -1;
	// 		}	
	// 		leftNeighbour = &_rightNum;
	// 	}
	// 	return exploded;
	// }

	// if(level == 4 && _left && !explosions) {
	// 	// std::cout << "Exploding L " << _left->toString() << std::endl;
	// 	Pair::explosions = true;
	// 	if (leftNeighbour)
	// 		*leftNeighbour += _left->_leftNum;
	// 	rightValueToAdd = _left->_rightNum;
	// 	_left = NULL;
	// 	_leftNum = 0;
	// }
	// else if (level == 4) {
	// 	leftNeighbour = &_leftNum;
	// 	if (rightValueToAdd != -1) {			
	// 		_leftNum += rightValueToAdd;
	// 		rightValueToAdd = -1;
	// 	}	
	// }
	// if(level == 4 && _right && !explosions) {
	// 	// std::cout << "Exploding R " << _right->toString() << std::endl;
	// 	Pair::explosions = true;
	// 	if (leftNeighbour)
	// 		*leftNeighbour += _right->_leftNum;
	// 	rightValueToAdd = _right->_rightNum;
	// 	_right = NULL;
	// 	_rightNum = 0;
	// }
	// else if (level == 4) {
	// 	leftNeighbour = &_rightNum;
	// 	if (rightValueToAdd != -1) {			
	// 		_rightNum += rightValueToAdd;
	// 		rightValueToAdd = -1;
	// 	}	
	// }
// 	return false;
// }