#include "UserFunction.h"
#include "Token.h"

#include <string>
#include <vector>
#include <stack>
#include <iostream>


UserFunction::UserFunction(std::string input) : input_string(input){
	init();
}

UserFunction::UserFunction(){
	init();
}

void UserFunction::init(){
	//Order is important here. Inverse trig function must come before the trig function itself.
	valid_functions.push_back("acos");
	valid_functions.push_back("asin");
	valid_functions.push_back("atan");
	valid_functions.push_back("cos");
	valid_functions.push_back("sin");
	valid_functions.push_back("tan");
	valid_functions.push_back("ln");
}

std::vector<Token> UserFunction::shuntingYard(std::vector<Token> tokens){
	std::stack<Token> operator_stack;
	std::vector<Token> output;
	unsigned int index = 0;
	unsigned int num_tokens = tokens.size();
	
	
	while(index < num_tokens){
		Token curr_token = tokens[index];
		if(curr_token.isNumber()){
			output.push_back(curr_token);
		}
		else if(curr_token.isOperator()){
			if(!operator_stack.empty()){
				while(operator_stack.top().isOperator()
						&& 
						( (curr_token.isLeftAssoc() && curr_token.getPrecedence() <= operator_stack.top().getPrecedence())
						  ||
						  (curr_token.getPrecedence() < operator_stack.top().getPrecedence()) )
					  )
				{
					output.push_back(operator_stack.top());
					operator_stack.pop();
				}
			}
			operator_stack.push(curr_token);
		}
		else if(curr_token.getStr() == "("){
			operator_stack.push(curr_token);
		}
		else if(curr_token.getStr() == ")"){
			while(operator_stack.top().getStr() != "("){
				output.push_back(operator_stack.top());
				operator_stack.pop();
				if(operator_stack.empty()){
					//error, mismatched parentheses
					break;
				}
			}
			if(operator_stack.top().getStr() == "("){
				operator_stack.pop();
			}
		}
		index++;
	}
	while(!operator_stack.empty()){
		if(operator_stack.top().getStr() == "(" || operator_stack.top().getStr() == ")"){
			//error, mismatched parentheses
			break;
		}
		else{
			output.push_back(operator_stack.top());
			operator_stack.pop();
		}
	}
	return output;
	
}

std::vector<Token> UserFunction::tokenize(std::string input){
	unsigned int index = 0;
	
	std::vector<Token> tokens;
	std::vector<std::string> functions;
	
	Token token;
	
	//Find the functions in input string
	for(unsigned int i = 0; i < valid_functions.size(); i++){
		unsigned int pos = input.find(valid_functions[i], 0);
		while(pos != std::string::npos){
			input.replace(pos, valid_functions[i].size(), "@");
			functions.push_back(valid_functions[i]);
			pos = input.find(valid_functions[i], pos + 1);
		}
	}
	
	unsigned int input_size = input.size();
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

bool UserFunction::process(){
	std::vector<Token> tokens = tokenize(input_string);
	//std::vector<Token> s_yard = shuntingYard(tokens);
	for(unsigned int i = 0; i < tokens.size(); i++){
		std::cout << tokens[i].getStr() << std::endl;
	}
	return true;
}

bool UserFunction::process(std::string input){
	std::vector<Token> tokens = tokenize(input);
	std::vector<Token> s_yard = shuntingYard(tokens);
	return true;
}

void UserFunction::setString(std::string input){
	input_string = input;
}

std::string UserFunction::getString(){
	return input_string;
}