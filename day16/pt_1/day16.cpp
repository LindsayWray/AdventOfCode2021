#include "Packet.hpp"

int main(){
	std::string binaryString;

	std::ifstream input("../input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	std::string hexaLine;
	input >> hexaLine;
	input.close();

	for(int i = 0; i < hexaLine.length(); i++){
		std::stringstream ss;
		ss << std::hex << hexaLine[i];
		unsigned n;
		ss >> n;
		std::bitset<4> bits(n);
		binaryString += bits.to_string();
	}
	std::cout << binaryString << std::endl;

	int index = 0;
	Packet P(binaryString, index);

	std::cout << Packet::versionsTotal << std::endl;
}