/*
 * maxtwo.cpp
 *
 *  Created on: Sep 7, 2022
 *      Author: ubuntu
 */
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
/*
 * Computes the max of two integers m and n.
 */
int max(int m, int n) {
	return m > n ? m : n;
}

int main(int argc, char* argv[]) {
	int m, n;
	istringstream iss; // input string stream variable

	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> m)) { // Read one integer from iss and check for failure too.
		cerr << "Error: the first argument is not a valid integer" << endl;
		return 1;
	}
	iss.clear(); // Remember to clear iss before using it with another string!
	iss.str(argv[2]);
	if(!(iss >> n)) {
		cerr << "Error: the second argument is not a valid integer" << endl;
		return 1;
	}
	cout << "m is: " << m << endl;
	cout << "n is: " << n << endl;
	cout << "max(" << m << ", " << n << ") is: " << max(m, n) << endl;

	cout <<fixed; // so it does not use signtificing notation
	cout<< setprecision(20); // allows how many decimal points
	cout << 1.0/30000.0 << endl;
	return 0;
}




