#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <getopt.h>

#include "UserFunction.h"
#include "boost/lexical_cast.hpp"
using namespace std;

typedef vector<pair<float, float>> discrete_fn; 

float evaluateIntegral(UserFunction fn1, UserFunction fn2, float t_shift, int num_points);
discrete_fn evaluateFunction(UserFunction fn, float t_min, float t_max, int num_points);
discrete_fn convolve(UserFunction fn1_eval, UserFunction fn2_eval, unsigned int num_points);
void fixZeros(discrete_fn& fn);
void printHelp();


int main(int argc, char* argv[]){
    string fn1_input, fn2_input;
    float t1_min, t1_max, t2_min, t2_max;
    int num_points = 100;

    int c;
    int help_flag;
    while(1){
        static struct option long_options[] = {
            {"fn1", required_argument, 0, 'f'},
            {"fn2", required_argument, 0, 'g'},
            {"t1min", required_argument, 0, 'a'},
            {"t1max", required_argument, 0, 'b'},
            {"t2min", required_argument, 0, 'c'},
            {"t2max", required_argument, 0, 'd'},
            {"datapoints", required_argument, 0, 'p'},
            {"help", no_argument, &help_flag, 'h'}
        };
        int option_index = 0;
        c = getopt_long (argc, argv, "f:g:i:e:p:h", long_options, &option_index);
        if(c == -1) break;

        switch(c){
            case 0:
                if(long_options[option_index].flag != 0) break;
                //cout << long_options[option_index].name << endl;
                //cout << "Arg: " << optarg << endl;
            case 'f':
                fn1_input = (string) optarg;
                break;
            case 'g':
                fn2_input = (string) optarg;
                break;
            case 'a':
                t1_min = boost::lexical_cast<float>(optarg);
                break;
            case 'b':
                t1_max = boost::lexical_cast<float>(optarg);
                break;
            case 'c':
                t2_min = boost::lexical_cast<float>(optarg);
                break;
            case 'd':
                t2_max = boost::lexical_cast<float>(optarg);
                break;
            case 'p':
                num_points = boost::lexical_cast<int>(optarg);
                break;
            case 'h':
                printHelp();
                return 0;
                break;
            case '?':
                return 0;
                break;
            default:
                printHelp();
        }
    }
            

    /*
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
	
	unsigned int num_points = 20;
    */
    UserFunction fn1 = UserFunction(fn1_input, t1_min, t1_max);
    fn1.process();
    UserFunction fn2 = UserFunction(fn2_input, t2_min, t2_max);
    fn2.process();
    
	//float spacing = (t_max - t_min)/(num_points - 1);
    //cout << evaluateIntegral(fn1, t_min, t_max, num_points) << endl;
    //discrete_fn fn_convolve = convolve(fn1, fn2 num_points);
	/*
    discrete_fn fn1_eval = evaluateFunction(fn1, t_min, t_max, num_points);
    discrete_fn fn2_eval = evaluateFunction(fn2, t_min, t_max, num_points);

	discrete_fn fn_convolve = convolve(fn1_eval, fn2_eval, t_min, t_max, num_points);
    fixZeros(fn_convolve);
    */
    //print t vector
    discrete_fn fn_convolve = convolve(fn1, fn2, num_points);//evaluateFunction(fn1, -10, 30, num_points);
    cout << "t = linspace(" << fn_convolve[0].first << ", " << fn_convolve[fn_convolve.size() - 1].first << ", " << fn_convolve.size() << ");" << endl;
    cout << "f_t = [";
    for(unsigned int i = 0; i < fn_convolve.size(); i++){
        cout << fn_convolve[i].second;
        if(i != fn_convolve.size() - 1){
            cout << ", ";
        }
    }
    cout << "];" << endl;
    
}

float evaluateIntegral(UserFunction fn1, UserFunction fn2, float t_shift, int num_points){
    //Take more time and write this function in a more intuitive way. This doesn't work as it is anyway.
    float curr_t, val1, val2;
    //Need to evaluate the integral from -infinite to +infinite, but each function only exists between t_min and t_max
    //So we need to find the bounds in which either fn1 or the flipped version of fn2 exists
    float lower_lim = fn1.t_min;
    float upper_lim = fn1.t_max;
    int integral_divisions = 500;

    float sum = 0;
    float rect_width = (upper_lim - lower_lim)/integral_divisions;
    for(int i = 0; i < integral_divisions; i++){
        curr_t = lower_lim + i*rect_width;
        val1 = fn1.evaluate(curr_t);
        val2 = fn2.evaluate(t_shift - curr_t);
        sum += rect_width*(val1*val2);
    }
    return sum;
}

discrete_fn evaluateFunction(UserFunction fn, float t_min, float t_max, int num_points){
    float spacing = (t_max - t_min)/(num_points - 1);
	discrete_fn output;
	for(int i = 0; i < num_points; i++){
		float t = t_min + i*spacing;
		output.push_back(make_pair(t, fn.evaluate(t)));
	}
	return output;
}

discrete_fn convolve(UserFunction fn1, UserFunction fn2, unsigned int num_points){
    //fn1 is stationary, fn2 is flipped and shifted
    //t_shift = how far to shift left
    float t_shift_start = fn1.t_min + fn2.t_min;
    float t_shift_end = t_shift_start + (fn1.t_max - fn1.t_min) + (fn2.t_max - fn2. t_min);
    float spacing = (t_shift_end - t_shift_start)/(num_points - 1);
    discrete_fn output;
    
    //We have determined the limits between which the convolution integral must be calculated
    //Now, flip and then shift fn2 and calculate the value at each position
    for(unsigned int i = 0; i < num_points; i++){
        float t_shift = t_shift_start + i*spacing;
        output.push_back(make_pair(t_shift, evaluateIntegral(fn1, fn2, t_shift, num_points)));
    }
    return output;
}

//Since we're using floating point arithmetic, zeroes are being returned as something on the order of 10^-12
//This function sets all values who's absolute value is < 0.5% of the average value of the function = 0
void fixZeros(discrete_fn& fn){
    float sum = 0;

    for(unsigned int i = 0; i < fn.size(); i++){
        sum += fn[i].second;    
    }
    float avg = abs(sum/fn.size());

    for(unsigned int i = 0; i < fn.size(); i++){
        if(abs(fn[i].second) < avg*.005){
            fn[i].second = 0;
        }
    }
}

void printHelp(){
    cout << "Usage" << endl;
    return;
}
