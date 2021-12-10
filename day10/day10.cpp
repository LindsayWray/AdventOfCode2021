#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool	isOpening(char c){
	if (c == '(' || c == '[' || c == '{' || c == '<')
		return true;
	return false;
}

bool	isMatch(char c, char top){
	if (c == ')' && top == '('
		|| c == ']' && top == '['
		|| c == '}' && top == '{'
		|| c == '>' && top == '<')
			return true;
	return false;
}

int	syntaxCheck(std::string line){
	std::stack<char> syntaxStack;

	for(int i = 0; i < line.length(); i++){
		if (isOpening(line[i])){
			syntaxStack.push(line[i]);
		}
		else if(isMatch(line[i], syntaxStack.top()))
			syntaxStack.pop();
		else{
			if (line[i] == ')')
				return 3;
			if (line[i] == ']')
				return 57;
			if (line[i] == '}')
				return 1197;
			if (line[i] == '>')
				return 25137;
		}
	}
	return 0;
}

int main(){

std::vector<std::string> lines;

	std::ifstream input("input");
	if (!input.is_open()){
		std::cerr << "Could not open file\n";
		exit(EXIT_FAILURE);
	}

	std::string line;
	do {
		input >> line;
		lines.push_back(line);
	} while (!input.eof());
	input.close();


	long long answer = 0;
	for(int i = 0; i < lines.size(); i++){
		answer += syntaxCheck(lines[i]);
	}
	std::cout << answer << std::endl;
}