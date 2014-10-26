#ifndef TOKENIZED_FUNCTION_H
#define TOKENIZED_FUNCTION_H

#include <string>
#include <vector>

class TokenizedFunction{
    
    private:
        std::string input_string;
        std::vector<std::string> valid_tokens;
        std::vector<Token> token_list;
        bool tokenize(std::string expression);
        std::vector<std::string> lookup(std::string curr_word, std::vector<std::string> possible_tokens);
        void printVec(std::vector<std::string> vec);

    public:
        UserFunction(std::string input);
        UserFunction();
        bool process();
		bool process(std::string input);
        void setString(std::string input);
        std::string getString();

};


#endif
