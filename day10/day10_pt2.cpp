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

long	fixStack(std::stack<char> syntaxStack){
	long score = 0;
	while(!syntaxStack.empty()){
		if (syntaxStack.top() == '(')
			score = (score * 5) + 1;
		if (syntaxStack.top() == '[')
			score = (score * 5) + 2;
		if (syntaxStack.top() == '{')
			score = (score * 5) + 3;
		if (syntaxStack.top() == '<')
			score = (score * 5) + 4;
		syntaxStack.pop();
	}
	return score;
}

long	syntaxCheck(std::string line){
	std::stack<char> syntaxStack;

	for(int i = 0; i < line.length(); i++){
		if (isOpening(line[i])){
			syntaxStack.push(line[i]);
		}
		else if(isMatch(line[i], syntaxStack.top()))
			syntaxStack.pop();
		else{
			return 0;
		}
	}
	return fixStack(syntaxStack);
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



	std::vector<long> scores;
	for(int i = 0; i < lines.size(); i++){
		long score = syntaxCheck(lines[i]);
		if (score != 0)
			scores.push_back(score);
	}

	std::sort(scores.begin(), scores.end());
	long long answer = scores[scores.size() / 2];
	std::cout << answer << std::endl;
}