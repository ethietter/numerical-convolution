#include "Token.h"
#include "boost/lexical_cast.hpp"
#include <string>
#include <vector>
#include <regex>
#include <iostream>

enum token_ids{
	ID_OPERATOR,
	ID_NUMBER,
	ID_VAR,
	ID_UNDEFINED
};

Token::Token(std::string str) : token_string(str) {
	is_partial = true;
	token_type = ID_UNDEFINED;
	setType();
}

Token::Token(){
	is_partial = true;
	token_type = ID_UNDEFINED;
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
		if(isFloat(token_string)){
			token_type = ID_NUMBER;
		}
	}
	else if(token_string.size() > 1){
		if(isFloat(token_string)){
			token_type = ID_NUMBER;
		}
	}
}

bool Token::isFloat(std::string str){
	try {
		boost::lexical_cast<float>(str);
		return true;
	}
	catch(boost::bad_lexical_cast){
		return false;
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

bool Token::appendStr(std::string str){
	/*if(is_partial){
		token_string += str;
		setType();
	}
	*/
	if(is_partial){
		if(token_type == ID_NUMBER){
			//Does adding the char to this make it a number? If so, add the char to the token string and return true
			if(isFloat(token_string + str)){
				token_string += str;
				return true;
			}
			else{
				return false;
			}
		}
		token_string += str;
		setType();
	}
	return false;
}

bool Token::appendStr(char c){
	if(is_partial){
		if(token_type == ID_NUMBER){
			//Does adding the char to this make it a number? If so, add the char to the token string and return true
			if(isFloat(token_string + c)){
				token_string += c;
				return true;
			}
			else{
				return false;
			}
		}
		token_string += c;
		setType();
	}
	return false;
}

void Token::setStr(std::string str){
	token_string = str;
	setType();
}

void Token::setStr(char c){
	token_string = c;
	//std::cout << token_string << " <-- In setStr() " << std::endl;
	setType();
}

std::string Token::getStr(){
    return token_string;
}

void Token::reset(){
	token_string = "";
	token_type = ID_UNDEFINED;
	is_partial = true;
}