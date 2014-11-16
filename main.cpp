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

discrete_fn evaluateFunction(UserFunction fn, float x_min, float x_max, int num_points);
discrete_fn convolve(discrete_fn fn1_eval, discrete_fn fn2_eval, float t_min, float t_max, unsigned int num_points);
void fixZeros(discrete_fn& fn);
void printHelp();


int main(int argc, char* argv[]){
    string fn1_input, fn2_input;
    float t_min, t_max;
    int num_points = 100;

    int c;
    int help_flag;
    while(1){
        static struct option long_options[] = {
            {"fn1", required_argument, 0, 'f'},
            {"fn2", required_argument, 0, 'g'},
            {"tmin", required_argument, 0, 'i'},
            {"tmax", required_argument, 0, 'e'},
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
            case 'i':
                t_min = boost::lexical_cast<float>(optarg);
                break;
            case 'e':
                t_max = boost::lexical_cast<float>(optarg);
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
    UserFunction fn1 = UserFunction(fn1_input);
    fn1.process();
    UserFunction fn2 = UserFunction(fn2_input);
    fn2.process();

	//float spacing = (t_max - t_min)/(num_points - 1);
	discrete_fn fn1_eval = evaluateFunction(fn1, t_min, t_max, num_points);
    discrete_fn fn2_eval = evaluateFunction(fn2, t_min, t_max, num_points);

	discrete_fn fn_convolve = convolve(fn1_eval, fn2_eval, t_min, t_max, num_points);
    fixZeros(fn_convolve);

    //print t vector
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

discrete_fn evaluateFunction(UserFunction fn, float t_min, float t_max, int num_points){
    float spacing = (t_max - t_min)/(num_points - 1);
	discrete_fn output;
	for(int i = 0; i < num_points; i++){
		float t = t_min + i*spacing;
		output.push_back(make_pair(t, fn.evaluate(t)));
	}
	return output;
}

discrete_fn convolve(discrete_fn fn1_eval, discrete_fn fn2_eval, float t_min, float t_max, unsigned int num_points){
    //fn1 is stationary, fn2 is flipped and shifted
    //t_shift = how far to shift left
    float spacing = (t_max - t_min)/(num_points - 1);
    float t_shift = max(-t_min, -t_max) - min(t_min, t_max);
    discrete_fn output;

    for(unsigned int i = 0; i < 2*num_points - 1; i++){
        float sum = 0;
        //Sum all of the points that overlap
        //Number of overlapping points =                i + 1, i < num_points
        //                               num_points*2 - i - 1, i >= num_points
        unsigned int overlap_count = (i <= num_points) ? (i + 1) : (num_points*2 - i - 1);
        for(unsigned int j = 0; j < overlap_count; j++){
            sum += fn1_eval[j].second*fn1_eval[num_points - j].second;
        }
        output.push_back(make_pair(i*spacing - t_shift, sum));
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
