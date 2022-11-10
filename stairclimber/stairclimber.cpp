/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Kush Parmar
 * Date        : 10/1/2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that i have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	vector<vector<int>> ways;
	vector<vector<int>> result;
	if(num_stairs<=0){ // if statement breaks recursion or if stairs equal 0
		ways.push_back(vector<int>());
		return ways;
	}
	for(int i =1; i <4;i++){ // number of stairs
		if (num_stairs>=i){ // makes sure that we don't enter negative or 0 steps
			result= get_ways(num_stairs-i); //recursive calls to check how many ways you can climb up stairs from 1-3
			for(auto it: result){
				it.insert(it.begin(),i); //appends i at the beginning of list
				ways.push_back(it); //appends results in to ways
				}
			}
		}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int size_max_digits=(int)ways.size();
	int space=0;
	while(size_max_digits>0){ //while loop calculates how much space is needed for printing
		space++;
		size_max_digits/=10;
	}
	for(size_t i =0; i<ways.size(); i++){// iterates through ways
		cout<<setw(space)<<i+1<<". [";
		for(size_t j=0; j<ways[i].size();j++){
			cout<<ways[i][j];
			if((int)j<=((int)ways[i].size()-2)){
				cout<<", ";
			}
		}
		cout<<"]"<<endl;
	}


}

int main(int argc, char * const argv[]) {
	if(argc==1){ //checks amount of inputs
		cerr<<"Usage: ./stairclimber <number of stairs>"<<endl;
		return 1;
	}
	if(argc>2){ //checks amount of inputs
		cerr<<"Usage: ./stairclimber <number of stairs>"<<endl;
		return 1;
	}
    istringstream iss(argv[1]);
    int num_stair=0;
    if(!(iss>>num_stair)){ //checks if input is int
    	cerr<<"Error: Number of stairs must be a positive integer."<<endl;
    	return 1;
    }
    if(num_stair<=0){ ////checks amount of above 0
    	cerr<<"Error: Number of stairs must be a positive integer."<<endl;
    	return 1;
    }
    else{
    	vector<vector<int>> results = get_ways(num_stair);
    	if(num_stair==1){
        	cout<<(int) results.size() <<" way to climb "<< num_stair<< " stair."<<endl;
        	display_ways(results);
        	return 0;
    	}
    	else{
    		cout<<(int) results.size() <<" ways to climb "<< num_stair<< " stairs."<<endl;
    		display_ways(results);
    		return 0;
    	}
    }


}
