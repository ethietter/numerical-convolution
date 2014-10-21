#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include <string>
#include <vector>
#include "Token.h"

class UserFunction{
    
    private:
        std::string input_string;
        std::vector<std::string> valid_tokens;
        std::vector<Token> token_list;
        void tokenize();
        std::vector<std::string> lookup(std::string curr_word, std::vector<std::string> possible_tokens);

    public:
        UserFunction(std::string input);
        UserFunction();
        void process(); 
        void setString(std::string input);
        std::string getString();

};


#endif
