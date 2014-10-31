#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token{
    
    private:
        std::string token_string;
		float float_val;
		int token_type;
		unsigned int precedence;
		bool float_val_set = false;
		bool is_left_assoc;
		bool is_partial;
		void setType();
		bool isFloat(std::string str);

    public:
		Token(std::string str, bool is_function);
        Token(std::string str);
		Token();
        std::string getStr();
		bool isPartial();
		void setComplete();
		bool appendStr(char c);
		void setStr(char c);
		void setFunction(std::string str);
		void reset();
		int getType();
		unsigned int getPrecedence();
		bool isLeftAssoc();
		bool isOperator();
		bool isNumber();
		bool isVar();
		bool isFunction();
		float getFloatVal();
		void setFloat(float val);

};


#endif
