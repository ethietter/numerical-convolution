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
	ID_PAREN,
	ID_FUNCTION,
	ID_UNDEFINED
};

Token::Token(std::string str) : token_string(str) {
	is_partial = true;
	float_val_set = false;
	token_type = ID_UNDEFINED;
	setType();
}

Token::Token(){
	is_partial = true;
	float_val_set = false;
	token_type = ID_UNDEFINED;
}

Token::Token(std::string str, bool is_function) : token_string(str){
	if(is_function){
		setFunction(str);
	}
	else{
		is_partial = true;
		token_type = ID_UNDEFINED;
		setType();
	}
}

void Token::setType(){
	char operators[] = {'+', '-', '*', '/', '^'};
	if(token_string.size() == 1){
		if(token_string[0] == 't'){
			is_partial = false;
			token_type = ID_VAR;
			return;
		}
		if(token_string[0] == '@'){
			is_partial = false;
			token_type = ID_FUNCTION;
			return;
		}
		if(token_string[0] == '(' || token_string[0] == ')'){
			is_partial = false;
			token_type = ID_PAREN;
			return;
		}
		for(unsigned int i = 0; i < sizeof(operators)/sizeof(operators[0]); i++){
			if(token_string[0] == operators[i]){
				is_partial = false;
				token_type = ID_OPERATOR;
				if(operators[i] == '+' || operators[i] == '-'){
					precedence = 0;
					is_left_assoc = true;
				}
				if(operators[i] == '*' || operators[i] == '/'){
					precedence = 1;
					is_left_assoc = true;
				}
				if(operators[i] == '^'){
					precedence = 2;
					is_left_assoc = false;
				}
				return;
			}
		}
		//If it gets here, it's neither an operator nor a variable
		if(isFloat(token_string) || token_string[0] == '.'){
			token_type = ID_NUMBER;
		}
	}
	else if(token_string.size() > 1){
		if(isFloat(token_string)){
			token_type = ID_NUMBER;
		}
	}
}

bool Token::isLeftAssoc(){
	return is_left_assoc;
}

unsigned int Token::getPrecedence(){
	return precedence;
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

bool Token::isOperator(){
	return (token_type == ID_OPERATOR);
}

bool Token::isNumber(){
	return (token_type == ID_NUMBER);
}

bool Token::isVar(){
	return (token_type == ID_VAR);
}

bool Token::isFunction(){
	return (token_type == ID_FUNCTION);
}

bool Token::appendStr(char c){
	if(is_partial){
		if(c == '@') return false;//It's a function
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

void Token::setStr(char c){
	token_string = c;
	setType();
}

void Token::setFunction(std::string str){
	token_string = str;
	token_type = ID_FUNCTION;
	is_partial = false;
}

std::string Token::getStr(){
    return token_string;
}

void Token::reset(){
	token_string = "";
	token_type = ID_UNDEFINED;
	is_partial = true;
}

float Token::getFloatVal(){
    try {
        return boost::lexical_cast<float>(token_string);
    }
    catch(boost::bad_lexical_cast){
        return 0;
    }
	return 0;
}

void Token::setFloat(float val){
	float_val = val;
	token_string = boost::lexical_cast<std::string>(float_val);
	float_val_set = true;
	setComplete();
}
