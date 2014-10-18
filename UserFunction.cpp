#include "UserFunction.h"
#include <string>
#include <iostream>

UserFunction::UserFunction(std::string input) :input_string(input) {
    std::string valid_tokens_list[] = {"(", ")", "+", "-", "/", "*", "^", "t", "log", "ln", "pi", "e", "cos", "sin", "tan"};
    for(unsigned int i = 0; i < sizeof(valid_tokens_list) / sizeof(valid_tokens_list[0]); i++){
        this->valid_tokens.push_back(valid_tokens_list[i]);
    }
}

void UserFunction::tokenize(){
    std::vector<std::string> possible_tokens(valid_tokens.begin(), valid_tokens.end());
    std::string partial_token = "";
    for(unsigned int i = 0; i < this->input_string.length(); i++){
        for(unsigned int j = 0; j < possible_tokens.size(); j++){
            if(input_string[i] == possible_tokens[j][partial_token.length()]){
                partial_token += input_string[i];
                if(partial_token == possible_tokens[j]){
                    Token new_token(partial_token);
                    this->token_list.push_back(new_token);
                    partial_token = "";
                }
            }
        }
    }
    for(unsigned int i = 0; i < this->token_list.size(); i++){
        std::cout << i << std::endl;
        //std::cout << *it << std::endl;
    }
}

void UserFunction::process(){
    this->tokenize();
}

void UserFunction::setString(std::string input){
    this->input_string = input;
}

std::string UserFunction::getString(){
    return this->input_string;
}

