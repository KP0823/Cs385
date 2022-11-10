/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Kush Parmar
 * Version : 1.0
 * Date    : September 7, 2022
 * Description: Computes the square root of two/one command-line arguments.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

double sqrt(double num, double epsilon){
	double last_guess, next_guess;
	if(num<0){
		return numeric_limits<double>::quiet_NaN(); //ask about this
		//return -1;
	}
	else if(num==1||num==0){
		return num;
	}
	else{
		next_guess = num;
		last_guess=0;
		while(!(abs(last_guess-next_guess)<=epsilon)){
			last_guess = next_guess;
			next_guess = (((last_guess+(num/last_guess))/2));
		}
		return next_guess;
	}

}

int main(int argc, char* argv[]){
	double num, ep;
	istringstream iss;

	cout<<fixed;
	cout<< setprecision(8);
	if(argc>3|| argc==1){
		cerr<<"Usage: ./sqrt <value> [epsilon]"<<endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss>>num)){
		cerr<< "Error: Value argument must be a double."<< endl;
		return 1;
	}
	iss.clear();
	if(argc==2){
		ep=0.0000007;
		cout<<sqrt(num,ep)<<endl;
		return 0;
	}
	iss.str(argv[2]);
	if(!(iss>>ep)){
		cerr<<"Error: Epsilon argument must be a positive double."<<endl;
		return 1 ;
	}
	iss.clear();
	if(ep<=0){
		cerr<<"Error: Epsilon argument must be a positive double."<<endl;
		return 1;
	}
	cout<<sqrt(num,ep)<<endl;
	return 0;
}





