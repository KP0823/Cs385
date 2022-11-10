/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Kush Parmar
 * Version     : 1.0
 * Date        : 10/28/2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that i have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long counter=0;							//counter that will be returned
	for(int i=0; i<length;i++){				//first for loop
		for(int j =i+1;j<length;j++){		//i+1 because the first parts of array[i] should be sorted
			if(array[i]>array[j]){			//compare value
				counter++;					// adds to counter
			}
		}
	}
	return counter;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int* scratch = new int [length];					//extra space
	long counter= mergesort(array,scratch,0,length-1);	//send to merge sort
	delete [] scratch;									//for valgrind :)
	return counter;
}
static long merge(int array[], int scratch[], int low,int mid, int high){
	long counter= 0;
	int i1=low;							//i1=low
	int i2=mid+1;						//i2=mid+1
	int i=low;							//i=low
	while ((i1<=mid) && (i2<=high)){	//checks values from i to mid, and i2 to high
		if (array[i1]<=array[i2]){		//swaps value at this condition
			scratch[i]= array[i1];
			i++;
			i1++;
		}
		else{
			scratch[i]=array[i2];		//else swaps here
			counter +=mid-i1+1;			//confusing counter increase
			i++;
			i2++;
		}
	}
	while(i1<=mid){						//moving up to grab rest value from first half
		scratch[i]=array[i1];
		i++;
		i1++;
	}
	while(i2<=high){					//moving up tp grab rest value from second half
		scratch[i]=array[i2];
		i++;
		i2++;
	}
	for(int i=low; i<=high; i++){		//copying value
		array[i]=scratch[i];
	}
	return counter;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long counter=0;
	if (low<high){
		int mid = low+(high-low)/2;
		counter= counter+ mergesort(array,scratch,low,mid);		//adds to counter
		counter= counter+ mergesort(array,scratch,mid+1,high);	//adds to counter
		counter= counter+ merge(array,scratch,low,mid,high);	//merge and add
	}
	return counter;
}


int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	if(argc>2){
		cerr<<"Usage: ./inversioncounter [slow]"<<endl;
		return 1;
	}
	if(argc==2){
		string slow= argv[1];
		if(slow!="slow"){
			cerr<<"Error: Unrecognized option '"<<argv[1]<<"'."<<endl;
			return 1;
		}
	}
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if(values.size()>0){
    	if(argc== 2){
    		cout<<"Number of inversions: "<<count_inversions_slow(&values[0],(int)values.size())<<endl;;
    		values.clear();
    		return 0;
    	}
    	else{
    		cout<<"Number of inversions: "<<count_inversions_fast(&values[0],(int)values.size())<<endl;
    		values.clear();
    		return 0;

    	}
    }
    else{
    	cerr<<"Error: Sequence of integers not received."<<endl;
    	return 0;
    }

    return 0;
}
