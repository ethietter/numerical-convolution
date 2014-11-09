#include <iostream>
#include <string>
#include <vector>

#include "UserFunction.h"
using namespace std;

vector<float> evaluateFunction(UserFunction fn, float x_min, float x_max, int num_points);
vector<float> convolve(vector<float> fn1_eval, vector<float> fn2_eval, float t_min, float t_max, int num_points);

int main(int argc, char* argv[]){    
	string fn1_input, fn2_input;
	float t_min, t_max;
	
	cout << "T min: ";
	while(!(cin >> t_min)){
		cout << "Please enter a valid float\nT min: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	
	cout << "T max: ";
	while(!(cin >> t_max)){
		cout << "Please enter a valid float\nT max: ";
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
	
	int num_points = 20;
	float spacing = (t_max - t_min)/(num_points - 1);
	vector<float> fn1_eval = evaluateFunction(fn1, t_min, t_max, num_points);
    vector<float> fn2_eval = evaluateFunction(fn2, t_min, t_max, num_points);
	convolve(fn1_eval, fn2_eval, t_min, t_max, spacing);
}

vector<float> evaluateFunction(UserFunction fn, float t_min, float t_max, int num_points){
    float spacing = (t_max - t_min)/(num_points - 1);
	vector<float> output;
	for(int i = 0; i < num_points; i++){
		float t = t_min + i*spacing;
		output.push_back(fn.evaluate(t));
	}
	return output;
}

vector<float> convolve(vector<float> fn1_eval, vector<float> fn2_eval, float t_min, float t_max, int num_points){
    //fn1 is stationary, fn2 is flipped and shifted
    //t_shift = how far to shift left
    float t_shift = max(-t_min, -t_max) - min(t_min, t_max);

    for(unsigned int i = 0; i < 2*num_points; i++){
        
    }
    std::cout << t_shift;
    return vector<float>();
}
