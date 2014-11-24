#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <getopt.h>

#include "UserFunction.h"
#include "boost/lexical_cast.hpp"

#define M_PI 3.14159265358979323846
using namespace std;

typedef vector<pair<float, float>> discrete_fn; 

float evaluateCIntegral(UserFunction fn1, UserFunction fn2, float t_shift, int num_points);
float getCoefficient(discrete_fn fn, int n, char which);
discrete_fn evaluateFunction(UserFunction fn, float t_min, float t_max, int num_points);
discrete_fn convolve(UserFunction fn1_eval, UserFunction fn2_eval, unsigned int num_points);
void fixZeros(discrete_fn& fn);
void printHelp();
void matlabPrint(discrete_fn fn_convolve, string spec);
void writeFourier(discrete_fn fn, int num_coefficients, int num_points);

int main(int argc, char* argv[]){
    string fn1_input, fn2_input;
    float t1_min, t1_max, t2_min, t2_max;
    int num_points = 100;

    int c, num_coefficients;
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
            {"fourier", required_argument, 0, 'r'},
            {"help", no_argument, &help_flag, 'h'},
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
            case 'r':
                num_coefficients = boost::lexical_cast<int>(optarg);
                break;
            case '?':
                return 0;
                break;
            default:
                printHelp();
        }
    }
            

    UserFunction fn1 = UserFunction(fn1_input, t1_min, t1_max);
    fn1.process();
    UserFunction fn2 = UserFunction(fn2_input, t2_min, t2_max);
    fn2.process();

    
    discrete_fn fn_convolve = convolve(fn1, fn2, num_points);
    fixZeros(fn_convolve);
    
    cout << "clf;\nhold on;" << endl;
    
    if(num_coefficients > 0){
        writeFourier(fn_convolve, num_coefficients, num_points);
    }

    matlabPrint(fn_convolve, "k");
    matlabPrint(evaluateFunction(fn1, t1_min, t1_max, num_points), "r");
    matlabPrint(evaluateFunction(fn2, t2_min, t2_max, num_points), "g");
}

void writeFourier(discrete_fn fn, int num_coefficients, int num_points){
    vector<float> a_n;
    vector<float> b_n;
    float period = fn[fn.size() - 1].first - fn[0].first;
    for(int i = 0; i < num_coefficients; i++){
        a_n.push_back(getCoefficient(fn, i, 'a'));
        b_n.push_back(getCoefficient(fn, i, 'b'));
    }
    cout << "t = linspace(" << fn[0].first << ", " << fn[fn.size() - 1].first << ", " << num_points << ");\n";
    //print a_0
    cout << "f_t = ";
    cout << "(1/2)*" << a_n[0];
    for(int i = 1; i < num_coefficients; i++){
        cout << " + " << a_n[i] << "*cos(" << i << "*pi*t/" << period << ")";
        cout << " + " << b_n[i] << "*sin(" << i << "*pi*t/" << period << ")";
    }
    cout << ";\n";
    cout << "plot(t, f_t, 'b');\n";
}
//char which = 'a' or 'b'
float getCoefficient(discrete_fn fn, int n, char which){
    int integral_divisions = fn.size();
    float sum = 0;
    float fn_val, trig_val;
    float lower_lim = fn[0].first;
    float upper_lim = fn[fn.size() - 1].first;
    float rect_width = (upper_lim - lower_lim)/integral_divisions;
    float period = upper_lim - lower_lim;
    for(int i = 0; i < integral_divisions; i++){
        fn_val = fn[i].second;
        if(which == 'a'){
            trig_val = cos(n*M_PI*fn[i].first/period);
        }
        else{
            trig_val = sin(n*M_PI*fn[i].first/period);
        }
        sum += rect_width*fn_val*trig_val;
    }
    return sum/period;
}
void matlabPrint(discrete_fn fn_convolve, string spec){
    cout << "t = linspace(" << fn_convolve[0].first << ", " << fn_convolve[fn_convolve.size() - 1].first << ", " << fn_convolve.size() << ");\n";
    cout << "f_t = [";
    fn_convolve[0].second = 0;
    fn_convolve[fn_convolve.size() - 1].second = 0;
    for(unsigned int i = 0; i < fn_convolve.size(); i++){
        cout << fn_convolve[i].second;
        if(i != fn_convolve.size() - 1){
            cout << ", ";
        }
    }
    cout << "];\n";
    cout << "plot(t, f_t, '" << spec << "');\n";
}

float evaluateCIntegral(UserFunction fn1, UserFunction fn2, float t_shift, int num_points){
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
        output.push_back(make_pair(t_shift, evaluateCIntegral(fn1, fn2, t_shift, num_points)));
    }
    return output;
}

//Since we're using floating point arithmetic, zeroes are being returned as something on the order of 10^-12
//This function sets all values who's absolute value is < 0.05% of the average value of the function = 0
void fixZeros(discrete_fn& fn){
    float sum = 0;

    for(unsigned int i = 0; i < fn.size(); i++){
        sum += fn[i].second;    
    }
    float avg = abs(sum/fn.size());

    for(unsigned int i = 0; i < fn.size(); i++){
        if(abs(fn[i].second) < avg*.0005){
            fn[i].second = 0;
        }
    }
}

void printHelp(){
    cout << "Usage" << endl;
    return;
}
