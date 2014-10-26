#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token{
    
    private:
        std::string token_string;
		float float_val;
		int token_type;
		bool is_partial;
		void setType();
		void getFloatVal();

    public:
        Token(std::string str);
		Token();
        std::string getStr();
		bool isPartial();
		void setComplete();
		void appendStr(std::string str);
		void appendStr(char c);
		void setStr(std::string str);
		void setStr(char c);
		int getType();

};


#endif
