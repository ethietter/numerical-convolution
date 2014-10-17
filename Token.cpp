#include "Token.h"
#include <string>


Token::Token(std::string str) : token_string(str) {

}

std::string Token::getTokenString(){
    return this->token_string;
}
