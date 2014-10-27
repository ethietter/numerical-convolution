#include <iostream>
#include <string>

/* Shunting-Yard algorithm includes
[ */
#include <vector>
#include <stack>
#include "Token.h"
/*
] */
//#include "UserFunction.h"
//using namespace std;


std::vector<char> shuntingYard(std::string token_str){
	std::stack<char> operator_stack;
	std::vector<char> output;
	return output;
	//unsigned int str_index = 0;
	//unsigned int str_size = token_str.size();
	
	/*
	while(str_index < str_index){
		char curr_token = token_str[str_index];
		if(is
	}
	*/
	
}

/* Tokenizes a string that doesn't contain functions */
std::vector<Token> tokenize(std::string input){
	//Works perfectly except for recognizing leading decimals (i.e. "0.5" works, but ".5" does not)
	unsigned int index = 0;
	unsigned int input_size = input.size();
	
	std::vector<Token> tokens;
	
	Token token;
	
	for( ;index < input_size; index++){
		std::string token_str = token.getStr();
		if(token_str.empty()){
			token.setStr(input[index]);
		}
		else{
			if(token.appendStr(input[index])){
				continue;
			}
			else{
				tokens.push_back(Token(token.getStr()));
				token.reset();
				token.setStr(input[index]);
				if(!token.isPartial()){
					tokens.push_back(Token(token.getStr()));
					token.reset();
				}
			}
		}
	}
	
	if(!token.getStr().empty()){
		tokens.push_back(Token(token.getStr()));
	}
	
	return tokens;
}

int main(int argc, char* argv[]){
	std::string input;
	std::cin >> input;
	std::vector<Token> token_list = tokenize(input);
	std::cout << " -------------" << std::endl;
	for(unsigned int i = 0; i < token_list.size(); i++){
		std::cout << token_list[i].getStr() << std::endl;
	}
    /*
	string fn1_input, fn2_input;

    cout << "Input first function:" << endl;
    cin >> fn1_input;
    UserFunction fn1 = UserFunction(fn1_input);
    fn1.process();
    */
	/*
    cout << "Input second function:" <<endl;
    cin >> fn2_input;
    UserFunction fn2 = UserFunction(fn2_input);
    fn2.process();
	*/
}
