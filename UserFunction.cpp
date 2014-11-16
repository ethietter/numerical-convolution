#include "UserFunction.h"
#include "Token.h"

#include <math.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>


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
    valid_functions.push_back("exp");
}

std::vector<Token> UserFunction::shuntingYard(std::vector<Token> tokens){
	std::stack<Token> operator_stack;
	std::vector<Token> output;
	unsigned int index = 0;
	unsigned int num_tokens = tokens.size();
	
	
	while(index < num_tokens){
		Token curr_token = tokens[index];
		if(curr_token.isNumber() || curr_token.isVar()){
			output.push_back(curr_token);
		}
		else if(curr_token.isFunction()){
			operator_stack.push(curr_token);
		}
		else if(curr_token.isOperator()){
			while(!operator_stack.empty() && 
				  operator_stack.top().isOperator()
					&& 
					( (curr_token.isLeftAssoc() && curr_token.getPrecedence() <= operator_stack.top().getPrecedence())
					  ||
					  (curr_token.getPrecedence() < operator_stack.top().getPrecedence()) )
				  )
			{
				output.push_back(operator_stack.top());
				operator_stack.pop();
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
			if(operator_stack.top().isFunction()){
				output.push_back(operator_stack.top());
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
	//When a function is found, replace it with '@' and then push the function on to the functions vector
	for(unsigned int i = 0; i < valid_functions.size(); i++){
		unsigned int pos = input.find(valid_functions[i], 0);
		while(pos != std::string::npos){
			input.replace(pos, valid_functions[i].size(), "@");
			functions.push_back(valid_functions[i]);
			pos = input.find(valid_functions[i], pos + 1);
		}
	}
	
	unsigned int input_size = input.size();
	unsigned int function_index = 0;
	for( ;index < input_size; index++){
		std::string token_str = token.getStr();
		if(token_str.empty()){
			if(input[index] == '@'){
				token.setFunction(functions[function_index]);
				function_index++;
			}
			else{
				token.setStr(input[index]);
			}
		}
		else{
			if(token.appendStr(input[index])){
				continue;
			}
			else{
				tokens.push_back(Token(token.getStr(), token.isFunction()));
				token.reset();
				if(input[index] == '@'){
					token.setFunction(functions[function_index]);
					function_index++;
				}
				else{
					token.setStr(input[index]);
				}
				if(!token.isPartial()){
					tokens.push_back(Token(token.getStr(), token.isFunction()));
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
	s_yard = shuntingYard(tokens);
	/*for(unsigned int i = 0; i < s_yard.size(); i++){
		std::cout << s_yard[i].getStr() << " ";
	}*/
	return true;
}

void UserFunction::setString(std::string input){
	input_string = input;
}

std::string UserFunction::getString(){
	return input_string;
}

float UserFunction::evaluate(float t){
	std::stack<Token> eval_stack;
	for(unsigned int i = 0; i < s_yard.size(); i++){
		if(s_yard[i].isVar()){
			Token token;
			token.setFloat(t);
			eval_stack.push(token);
		}
		else if(s_yard[i].isNumber()){
			eval_stack.push(s_yard[i]);
		}
		else if(s_yard[i].isOperator()){
			float op_right = eval_stack.top().getFloatVal();
			eval_stack.pop();
			float op_left = eval_stack.top().getFloatVal();
			eval_stack.pop();
			eval_stack.push(evalOp(op_left, op_right, s_yard[i]));
		}
		else if(s_yard[i].isFunction()){
			float op = eval_stack.top().getFloatVal();
			eval_stack.pop();
			eval_stack.push(evalFn(op, s_yard[i]));
		}
	}
	
	if(eval_stack.size() != 1){
		std::cout << "Error in evaluate" << std::endl;
	}
	return eval_stack.top().getFloatVal();
}

Token UserFunction::evalOp(float op_left, float op_right, Token op){
	Token token;
	if(op.getStr() == "+") token.setFloat(op_left + op_right);
	else if(op.getStr() == "-") token.setFloat(op_left - op_right);
	else if(op.getStr() == "*") token.setFloat(op_left * op_right);
	else if(op.getStr() == "/") token.setFloat(op_left / op_right);
	else if(op.getStr() == "^") token.setFloat(pow(op_left, op_right));
	//std::cout << op_left << " " << op.getStr() << " " << op_right << std::endl;
	return token;
}

Token UserFunction::evalFn(float op, Token fn){
	Token token;
	if(fn.getStr() == "cos") token.setFloat(cos(op));
	else if(fn.getStr() == "sin") token.setFloat(sin(op));
	else if(fn.getStr() == "tan") token.setFloat(tan(op));
	else if(fn.getStr() == "acos") token.setFloat(acos(op));
	else if(fn.getStr() == "asin") token.setFloat(asin(op));
	else if(fn.getStr() == "atan") token.setFloat(atan(op));
	else if(fn.getStr() == "ln") token.setFloat(log(op));
    else if(fn.getStr() == "exp") token.setFloat(exp(op));
	return token;
}
