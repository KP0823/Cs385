/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Kush Parmar
 * Date        : Septemeber 15, 2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;


private:
    // Instance variables
    bool * const is_prime_; // this is the list pointer
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);

	int amount_per_row =1;//there was alot of guessing and checking
    if( num_primes()>primes_per_row){
    	for(int i = 2; i<=limit_;i++){
    		if(is_prime_[i]==true){
        		if(amount_per_row <primes_per_row){
        			if(i!=max_prime_){ // this checks whether its the last one or not
        				cout<<setw(max_prime_width)<<i<<" ";
        				amount_per_row++;
        			}
        			else if(i== max_prime_) {
        				cout<<setw(max_prime_width)<<i; // if it is the last prime it does not add space in the end
        			}
        		}
        		else{
        			amount_per_row=1;
        			cout<<setw(max_prime_width)<<i<<endl;
        		}
    		}
    	}
    }
    else if(num_primes()<=primes_per_row){
    	for(int i =2; i<=limit_;i++){
    		if(is_prime_[i]==true){
    			if(i!=max_prime_){
    				cout<<i<< " ";
    			}
    			if(i==max_prime_){
    				cout<<i;
    			}
    		}
    	}
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int counter=0;
	for(int i = 2; i<=limit_; i++){
		if(is_prime_[i]==true){
			counter++;
		}
	}
    return counter;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm

	//sets up is_prime by making all values true
	for(int createBool =2; createBool<=limit_;createBool++){
		is_prime_[createBool]=true;
	}
	//goes through and sorts out which are actually prime numbers
	for(int i =2; i<=sqrt(limit_);i++){
		if(is_prime_[i]==true){
			for(int j= i*i; j<=limit_;j+=i){
				is_prime_[j]=false;
			}
		}

	}
    num_primes_=count_num_primes();

    for(int k=2; k<=limit_;k++){
    	if(is_prime_[k]==true){
    		max_prime_=k;
    	}
    }

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int counter=0;
	while(num>0){
		num=num/10;
		counter++;
	}
    return counter;
}


int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    cout<<endl;
    PrimesSieve *newSieve =new PrimesSieve(limit);
    cout << "Number of primes found: " << (*newSieve).num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    (*newSieve).display_primes();
    delete newSieve;

    return 0;
}
