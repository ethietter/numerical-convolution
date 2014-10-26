#include "Token.h"
#include "boost/lexical_cast.hpp"
#include <string>
#include <vector>
#include <regex>
#include <iostream>

enum token_ids{
	ID_OPERATOR,
	ID_NUMBER,
	ID_VAR
};

Token::Token(std::string str) : token_string(str) {
	is_partial = true;
	setType();
}

Token::Token(){
	is_partial = true;	
}

void Token::setType(){
	char operators[] = {'+', '-', '*', '/', '^'};
	if(token_string.size() == 1){
		if(token_string[0] == 't'){
			is_partial = false;
			token_type = ID_VAR;
			return;
		}
		for(unsigned int i = 0; i < sizeof(operators)/sizeof(operators[0]); i++){
			if(token_string[0] == operators[i]){
				is_partial = false;
				token_type = ID_OPERATOR;
				return;
			}
		}
		//If it gets here, it's neither an operator nor a variable
		getFloatVal();
	}
	else if(token_string.size() > 1){
		getFloatVal();
	}
}

void getFloatVal(){
	try {
		float_val = boost::lexical_cast<float>(token_string);
		token_type = ID_NUMBER;
	}
	catch(boost::bad_lexical_cast){
		std::cout << "Invalid token" << std::endl;
	}
}

int Token::getType(){
	return token_type;
}

bool Token::isPartial(){
	return is_partial;
}

void Token::setComplete(){
	is_partial = false;
}

void Token::appendStr(std::string str){
	if(is_partial){
		token_string += str;
	}
	setType();
}

void Token::appendStr(char c){
	if(is_partial){
		token_string += c;
	}
	setType();
}

void Token::setStr(std::string str){
	token_string = str;
	setType();
}

void Token::setStr(char c){
	token_string = c;
	setType();
}

std::string Token::getStr(){
    return token_string;
}
