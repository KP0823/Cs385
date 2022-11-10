/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Kush Parmar
 * Date        : 9/28/2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	if(s.length()==0){
		return true;
	}
	for(auto &ch:s) {
		if(isupper(ch)){ //checks if the letter is upper if so then false
			return false;
		}
		if(!isalpha(ch)){ //checks if the char is an english letter if not then false;
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
	if(s.length()==0){
		return true;
	}
	unsigned int vector=0; //holds index of used letters
	for(auto &ch: s){
		int setter= ch-'a';
		if((vector & (1<<setter))==0){ // if 0's then good
			vector=(1<<setter)|vector; //concatenate the 1 at letter number bit
		}
		else{ // if it finds a 1 then its returns false
			return false;
		}
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	 if(argc==1){
		cerr<<"Usage: ./unique <string>"<<endl;
		return 1;
	 }
	 else if(argc>2){
		 cerr<<"Usage: ./unique <string>"<<endl;
		 return 1;
	 }
	 if(!is_all_lowercase(argv[1])){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	 }
	 if(!all_unique_letters(argv[1])){
		 cerr << "Duplicate letters found." << endl;
		return 1;
	 }
	 else if(all_unique_letters(argv[1])){
		cerr << "All letters are unique." << endl;
		return 0;
	 }
	return 0;
}
