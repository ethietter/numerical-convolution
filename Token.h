#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token{
    
    private:
        std::string token_string;

    public:
        Token(std::string str);
        std::string getTokenString();

};


#endif
