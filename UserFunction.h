#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include <string>

class UserFunction{
    
    private:
        std::string input_string;
        

    public:
        UserFunction(std::string input);
        UserFunction();
        void process(); 
        void setString(std::string input);
        std::string getString();

};


#endif
