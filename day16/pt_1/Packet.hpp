#ifndef PACKET_HPP
#define PACKET_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>

class Packet{
private:
	int _version;
	int _type;
	long _literal;
	int _lengthID;
	std::vector<Packet> _packets;

public:

	Packet(std::string binaryString, int &index);
	~Packet(){};

	long	findLiteral(std::string binaryString, int &index);
	void	findSubpackage(std::string binaryString, int &index);

	static	long versionsTotal;
};

#endif
