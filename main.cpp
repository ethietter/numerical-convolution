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
	unsigned int index = 0;
	unsigned int input_size = input.size();
	
	std::vector<Token> tokens;
	
	Token token;
	
	while(index < input_size){
		std::string token_str = token.getStr();
		if(token_str.empty()){
			token.setStr(input[index]);
		}
		else{
			//If it's of type number, look at the char to append. It has to be a number or a decimal, otherwise don't append
			token.appendStr(input[index]);
		}
		std::cout << token.getStr() << std::endl;
		index++;
		/*
		if(curr_token_str.isPartial()){
			curr_token_str .
		}
		*/
	}
	
	return tokens;
}

int main(int argc, char* argv[]){
	std::string input = "5*3.2";
	tokenize(input);
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
