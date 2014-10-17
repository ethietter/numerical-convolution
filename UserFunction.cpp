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

}

void UserFunction::process(){
    std::cout << "Process: " << this->input_string << std::endl;
}

void UserFunction::setString(std::string input){
    this->input_string = input;
}

std::string UserFunction::getString(){
    return this->input_string;
}

