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
		std::vector<Token> s_yard;
        std::vector<Token> token_list;
		std::vector<std::string> valid_functions;
        std::vector<Token> tokenize(std::string input);
		std::vector<Token> shuntingYard(std::vector<Token> tokens);
		void init();
		Token evalOp(float op_left, float op_right, Token op);
		Token evalFn(float op, Token fn);
		

    public:
        UserFunction(std::string input);
        UserFunction();
        bool process();
        void setString(std::string input);
        std::string getString();
		float evaluate(float t);

};


#endif
