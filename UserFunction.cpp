/*
 * USE BOOST SPIRIT PARSER FOR THIS. SIGNIFICANTLY EASIER
 *
 *
 */


#include "UserFunction.h"
#include <string>
#include <iostream>
#include <algorithm>

UserFunction::UserFunction(std::string input) :input_string(input) {
    std::string valid_tokens_list[] = {"(", ")", "+", "-", "/", "*", "^", "t", "log", "ln", "pi", "e", "cos", "sin", "tan"};
    for(unsigned int i = 0; i < sizeof(valid_tokens_list) / sizeof(valid_tokens_list[0]); i++){
        this->valid_tokens.push_back(valid_tokens_list[i]);
    }
}
std::vector<std::string> UserFunction::lookup(std::string curr_word, std::vector<std::string> possible_tokens){
    std::vector<std::string> new_tokens;
    unsigned int curr_word_length = curr_word.length();
    for(std::vector<std::string>::iterator it = possible_tokens.begin(); it != possible_tokens.end(); ++it){
        std::string found_word = "";
        unsigned int curr_token_length = (*it).length(); 
        for(unsigned int i = 0; i < std::max(curr_token_length, curr_word_length); i++){
            if(curr_word[i] == (*it)[i]){
                found_word += curr_word[i];
            }
            else{
                break;
            }
        }
        if(found_word != ""){
            new_tokens.push_back(*it);
        }
    }
    return new_tokens;
}

void UserFunction::printVec(std::vector<T> vec){
    for(std::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it){
        std::cout << *it << std::endl;
    }
}

void UserFunction::tokenize(){
    std::string current_word = "";
    std::vector<std::string> possible_tokens(valid_tokens.begin(), valid_tokens.end());
    for(unsigned int i = 0; i < this->input_string.length(); i++){
        //std::cout << current_word << std::endl;
        current_word += this->input_string[i];
        
        possible_tokens = lookup(current_word, possible_tokens);
        if(possible_tokens.size() == 1 && current_word == possible_tokens[0]){
            Token curr_token(possible_tokens[0]);
            this->token_list.push_back(curr_token);
            current_word = "";
            possible_tokens = valid_tokens;
        }
        else if(possible_tokens.size() == 0){
            possible_tokens = valid_tokens;
        }
    }
    for(std::vector<Token>::iterator it = token_list.begin(); it != token_list.end(); ++it){
        std::cout << (*it).getTokenString() << std::endl;
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

