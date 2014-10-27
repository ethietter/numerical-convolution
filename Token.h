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
		bool isFloat(std::string str);

    public:
        Token(std::string str);
		Token();
        std::string getStr();
		bool isPartial();
		void setComplete();
		bool appendStr(std::string str);
		bool appendStr(char c);
		void setStr(std::string str);
		void setStr(char c);
		void reset();
		int getType();

};


#endif
