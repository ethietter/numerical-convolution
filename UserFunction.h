#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include <string>
#include <vector>
#include <array>
#include "Token.h"

class UserFunction{
    
    private:
        std::string input_string;
        std::vector<std::string> valid_tokens;
        std::vector<Token> token_list;
        std::vector<Token> tokenize(std::string input);
		std::vector<Token> shuntingYard(std::vector<Token> tokens);
		std::vector<std::string> valid_functions;
		void init();
		

    public:
        UserFunction(std::string input);
        UserFunction();
        bool process();
		bool process(std::string input);
        void setString(std::string input);
        std::string getString();

};


#endif
