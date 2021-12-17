#include "Packet.hpp"

long Packet::versionsTotal = 0;

Packet::Packet(std::string binaryString, int &index){
	std::string version = binaryString.substr(index, 3);
	_version = strtol(version.c_str(), NULL, 2);
	versionsTotal += _version;
	index += 3;
	std::string type = binaryString.substr(index, 3);
	_type = strtol(type.c_str(), NULL, 2);
	index += 3;
	// std::cout << _version << std::endl;
	// std::cout << _type << std::endl;
	if(_type == 4){
		_literal = findLiteral(binaryString, index);
	}
	else
		findSubpackage(binaryString, index);
}

long Packet::findLiteral(std::string binaryString, int &index){
	std::string litValue;

	while(1){
		std::string group = binaryString.substr(index, 5);
		litValue += group.substr(1, 4);
		index += 5;
		if (group[0] == '0')
			break;
	}
	return strtol(litValue.c_str(), NULL, 2);
}

void	Packet::findSubpackage(std::string binaryString, int &index){
	_lengthID = binaryString[index];
	index++;

	if(_lengthID == '0'){
		std::string binary = binaryString.substr(index, 15);
		int lenSubPackets = strtol(binary.c_str(), NULL, 2);
		index += 15;
		int startIndex = index;
		while(index < startIndex + lenSubPackets){
			Packet sub(binaryString, index);
			_packets.push_back(sub);
		}
		
	}
	else{
		std::string binary = binaryString.substr(index, 11);
		int numberOfSubPackets = strtol(binary.c_str(), NULL, 2);
		index += 11;
		for(int i = 0; i < numberOfSubPackets; i++){
			Packet sub(binaryString, index);
			_packets.push_back(sub);
		}
	}
}

long	Packet::calculateValue(){
	if (_type == 4)
		return _literal;
	if (_type == 0){
		long sum = 0;
		for(int i = 0; i < _packets.size(); i++){
			sum += _packets[i].calculateValue();
		}
		return sum;
	}
	if (_type == 1){
		long product = 1;
		for(int i = 0; i < _packets.size(); i++){
			product *= _packets[i].calculateValue();
		}
		return product;
	}
	if (_type == 2){
		long min = LONG_MAX;
		for(int i = 0; i < _packets.size(); i++){
			long value = _packets[i].calculateValue();
			if (value < min)
				min = value;
		}
		return min;
	}
	if (_type == 3){
		long max = -1;
		for(int i = 0; i < _packets.size(); i++){
			long value = _packets[i].calculateValue();
			if (value > max)
				max = value;
		}
		return max;
	}
	if (_type == 5){
		long value1 = _packets[0].calculateValue();
		long value2 = _packets[1].calculateValue();
		if (value1 > value2)
			return 1;
		return 0;
	}
	if (_type == 6){
		long value1 = _packets[0].calculateValue();
		long value2 = _packets[1].calculateValue();
		if (value1 < value2)
			return 1;
		return 0;
	}
	if (_type == 7){
		long value1 = _packets[0].calculateValue();
		long value2 = _packets[1].calculateValue();
		if (value1 == value2)
			return 1;
		return 0;
	}
	return 0;
}