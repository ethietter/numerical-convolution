#include "UserFunction.h"
#include <string>
#include <iostream>

UserFunction::UserFunction(std::string input) :input_string(input) {
}

UserFunction::UserFunction(){

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

