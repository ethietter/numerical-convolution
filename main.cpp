#include <iostream>
#include <string>

#include "UserFunction.h"
using namespace std;



int main(int argc, char* argv[]){    
	string fn1_input, fn2_input;

    cout << "Input first function:" << endl;
    cin >> fn1_input;
    UserFunction fn1 = UserFunction(fn1_input);
    fn1.process();
    
	
    cout << "Input second function:" <<endl;
    cin >> fn2_input;
    UserFunction fn2 = UserFunction(fn2_input);
    fn2.process();
	
}
