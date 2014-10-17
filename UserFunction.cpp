#include "UserFunction.h"
#include <string>

UserFunction::UserFunction(std::string input){
    this.setString(input);
}

void UserFunction::UserFunction(){

}

void UserFunction::process(){
    std::cout << "Process: " << this.input_string << endl;
}

void UserFunction::setString(std::string input){
    this.input_string = input;
}

std::string UserFunction::getString(){
    return this.input_string;
}

