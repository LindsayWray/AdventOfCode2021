#include "Pair.hpp"

int * Pair::leftNeighbour = NULL;
int Pair::rightValueToAdd = -1;

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

Pair::Pair(Pair *pair1, Pair *pair2) : _left(pair1), _right(pair2){}


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

bool	Pair::explode(int level){
	bool exploded = false;

	if(level < 4){
		if(_left) {
		 	if (_left->explode(level + 1))
				if (!_right && rightValueToAdd != -1) {			
					_rightNum += rightValueToAdd;
					rightValueToAdd = -1;
				}
				return rightValueToAdd == -1;
		}
		else {
			if (rightValueToAdd != -1) {
				_leftNum += rightValueToAdd;
				rightValueToAdd = -1;
			}
				
			leftNeighbour = &_leftNum;
		}

		if(_right) {
			if (_right->explode(level + 1))
				return rightValueToAdd == -1;
		}
		else {
			if (rightValueToAdd != -1) {			
				_rightNum += rightValueToAdd;
				rightValueToAdd = -1;
			}	
			leftNeighbour = &_rightNum;
		}

		return exploded;
	}
	if(level == 4 && _left) {
		std::cout << "Exploding L " << _left->toString() << std::endl;
		if (leftNeighbour)
			*leftNeighbour += _left->_leftNum;
		rightValueToAdd = _left->_rightNum;
		_left = NULL;
		_leftNum = 0;
		return true;
	}
	if(level == 4 && _right) {
		std::cout << "Exploding R " << _right->toString() << std::endl;
		if (leftNeighbour)
			*leftNeighbour += _right->_leftNum;
		rightValueToAdd = _right->_rightNum;
		_right = NULL;
		_rightNum = 0;
		return true;
	}
	return false;
}