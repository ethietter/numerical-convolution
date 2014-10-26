#include "UserFunction.h"

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/lex_lexertl.hpp"
#include "boost/bind.hpp"
#include "boost/ref.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <stack>

namespace lex = boost::spirit::lex;

enum token_ids{
	ID_FUNC = 1000,
	ID_OPERATOR,
	ID_NUMBER,
	ID_VAR
};

template <typename Lexer>
struct function_tokens : lex::lexer<Lexer> {
	function_tokens(){
		// define tokens (the regular expression to match and the corresponding token id) and add them to the lexer
		this->self.add
			("[a-zA-Z]+\\[[^a-zA-Z]]*\\]", ID_FUNC)
			("([0-9]+(\\.)?[0-9]+)|([0-9]+)|((\\.)?[0-9]+)", ID_NUMBER)
			("[\\+\\-\\*/\\^]", ID_OPERATOR)
			("t", ID_VAR)
        ;
    }
};

struct counter {
	typedef bool result_type;
	
	template <typename Token>
	bool operator()(Token const& t) const {
		std::cout << "call" << std::endl;
		std::cout << t.value() << std::endl;
		/*switch(t.id(){
			case ID_WORD
			break;
		}*/
		return true;
	}
};


UserFunction::UserFunction(std::string input) :input_string(input) {
    /*std::string valid_tokens_list[] = {"(", ")", "+", "-", "/", "*", "^", "t", "log", "ln", "pi", "e", "cos", "sin", "tan"};
    for(unsigned int i = 0; i < sizeof(valid_tokens_list) / sizeof(valid_tokens_list[0]); i++){
        this->valid_tokens.push_back(valid_tokens_list[i]);
    }*/
}

bool UserFunction::process(std::string input){
	bool is_valid = this->tokenize(input);
	/*
	std::stack<char> input_stack;
	for(unsigned int i = 0; i < input.length(); i++){
		if(input[i] != ')'){
			input_stack.push(input[i]);
		}
		else{
			std::string curr_expression;
			char curr_char;
			while(!input_stack.empty() && ((curr_char = input_stack.top()) != '(')){
				curr_expression += curr_char;
				input_stack.pop();
			}
			if(!input_stack.empty() && input_stack.top() == '(') input_stack.pop();
			//Reverse the string
			unsigned int expr_len = curr_expression.length();
			for(unsigned int j = 0; j < ceil(expr_len/2.0); j++){
				char tmp = curr_expression[j];
				curr_expression[j] = curr_expression[expr_len - 1 - j];
				curr_expression[expr_len - 1 - j] = tmp;
			}
			this->tokenize(curr_expression);
			//std::reverse(&curr_expression, &curr_expression + curr_expression.length());
			//std::cout << curr_expression << std::endl;
		}
	}
    bool is_valid = this->tokenize(input);
	*/
	return is_valid;
	//return is_valid;
}

bool UserFunction::tokenize(std::string expression){
	function_tokens<lex::lexertl::lexer<> > tokenizer_functor;
	
	char const* first = expression.c_str();
	char const* last = &first[expression.size()];
	return lex::tokenize(first, last, tokenizer_functor, counter());//boost::bind(counter(), _1));
	
}

bool UserFunction::process(){
	return this->process(this->input_string);
	/*if(is_valid){
		std::cout << "Analysis successful" << std::endl;
	}
	else{
		std::string rest(first, last);
		std::cout << "Analysis failed\n Stopped at: \"" << rest << "\"\n" << std::endl;
	}*/
}


void UserFunction::setString(std::string input){
    this->input_string = input;
}

std::string UserFunction::getString(){
    return this->input_string;
}

void UserFunction::printVec(std::vector<std::string> vec){
    for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << std::endl;
    }
}