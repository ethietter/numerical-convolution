#include <iostream>
#include <string>
#include <vector>

#include "UserFunction.h"
using namespace std;

vector<float> evaluateFunction(UserFunction fn, float x_min, float x_max, int num_points);

int main(int argc, char* argv[]){    
	string fn1_input, fn2_input;
	float x_min, x_max;
	
	cout << "X min: ";
	while(!(cin >> x_min)){
		cout << "Please enter a valid float\nX min: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	
	cout << "X max: ";
	while(!(cin >> x_max)){
		cout << "Please enter a valid float\nX max: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}

    cout << "Input first function:" << endl;
    cin >> fn1_input;
    UserFunction fn1 = UserFunction(fn1_input);
    fn1.process();
    
	
    cout << "Input second function:" <<endl;
    cin >> fn2_input;
    UserFunction fn2 = UserFunction(fn2_input);
    fn2.process();
	
	num_points = 100;
	vector<float> fn1_eval = evaluateFunction(fn1, x_min, x_max, num_points);
	vector<float> fn2_eval = evaluateFunction(fn2, x_min, x_max, num_points);
	
}

vector<float> evaluateFunction(UserFunction fn, float x_min, float x_max, int num_points){
	vector<float> output;
	float offset = (x_max - x_min)/num_points;
	for(float t = x_min; t <= x_max; t += offset){
		output.push(fn.evaluate(t));
	}
	return output;
}
