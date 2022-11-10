/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Kush Parmar
 * Date        : 10/14/2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that i have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;


bool **visted; // boolean array

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
			a { _a }, b { _b }, c { _c }, directions { _directions }, parent {
					nullptr } {
	}

	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};
vector<State*> holder;
State* pour(State *cur, int pourFrom, int pourTo, State max) {
	State initial = *cur;
	int new_a = initial.a;
	int new_b = initial.b;
	int new_c = initial.c;
	int amount = 0;
	ostringstream newDirec; //string holding the direction
	if (pourFrom == 2 && pourTo == 0 && initial.a < max.a) { //c to a
		if ((max.a - initial.a) < initial.c) {
			amount = (max.a - initial.a);
			new_a = amount + initial.a;
			new_c = initial.c - amount;
		} else {
			new_a = initial.a + initial.c;
			new_c = initial.c - initial.c;
			amount = initial.c;
		}
	} else if (pourFrom == 1 && pourTo == 0 && initial.a < max.a) { //b to a
		if ((max.a - initial.a) < initial.b) {
			amount = (max.a - initial.a);
			new_a = amount + initial.a;
			new_b = initial.b - amount;
		} else {
			new_a = initial.a + initial.b;
			new_b = initial.b - initial.b;
			amount = initial.b;
		}
	} else if (pourFrom == 2 && pourTo == 1 && initial.b < max.b) { //c to b
		if ((max.b - initial.b) < initial.c) {
			amount = (max.b - initial.b);
			new_b = amount + initial.b;
			new_c = initial.c - amount;
		} else {
			new_b = initial.b + initial.c;
			new_c = initial.c - initial.c;
			amount = initial.c;
		}
	} else if (pourFrom == 0 && pourTo == 1 && initial.b < max.b) { //a to b
		if ((max.b - initial.b) < initial.a) {
			amount = (max.b - initial.b);
			new_b = amount + initial.b;
			new_a = initial.a - amount;
		} else {
			new_b = initial.b + initial.a;
			new_a = initial.a - initial.a;
			amount = initial.a;
		}
	} else if (pourFrom == 1 && pourTo == 2 && initial.c < max.c) { //b to c
		if ((max.c - initial.c) < initial.b) {
			amount = (max.c - initial.c);
			new_c = amount + initial.c;
			new_b = initial.b - amount;
		} else {
			new_c = initial.c + initial.b;
			new_b = initial.b - initial.b;
			amount = initial.b;
		}
	} else if (pourFrom == 0 && pourTo == 2 && initial.c < max.c) { //a to c
		if ((max.c - initial.c) < initial.a) {
			amount = (max.c - initial.c);
			new_c = amount + initial.c;
			new_a = initial.a - amount;
		} else {
			new_c = initial.c + initial.a;
			new_a = initial.a - initial.a;
			amount = initial.a;
		}
	}
	string choices = "ABC"; //string to choose
	State holder(new_a, new_b, new_c, ""); //temp to add to string
	if (amount == 1) {
		newDirec << "Pour " << amount << " gallon from " << choices[pourFrom]
				<< " to " << choices[pourTo] << ". " << holder.to_string();
	} else {
		newDirec << "Pour " << amount << " gallons from " << choices[pourFrom]
				<< " to " << choices[pourTo] << ". " << holder.to_string();
	}
	State* newjug= new State(new_a,new_b,new_c,newDirec.str()); //
	(*newjug).parent = cur; //set parent
	return newjug;

}
string printing(State *current) {
	string output = ""; //holds string
	while (current != nullptr) {
		if ((*current).parent != nullptr) {
			output = (*current).directions + '\n' + output; //concationated direction to output
			current = (*current).parent;
		} else {
			output = (*current).directions + " " + (*current).to_string() + '\n'+ output; //to concatenate the initial
			current = (*current).parent;
		}
	}
	return output;
}
bool check_in_holder(State *check) { //looks to see if check* is in the vector
	for (auto it : holder) {
		if ((*it).a==(*check).a &&(*it).b==(*check).b &&(*it).c==(*check).c) {
			return true;
		}
	}
	return false;
}
void clearing() { // deleted vector free heap
	for (size_t it = 0; it<holder.size();it++) {
		delete holder[it];
	}
	holder.clear();
}
int bfs(State *initial, State goal, State max) {
	queue<State*> track; //queue of state pointers
	track.push(initial);
	while (!(track.empty())) {
		State *current = track.front(); //front of the queue
		track.pop();
		if ((*current).a == goal.a && (*current).b == goal.b
				&& (*current).c == goal.c) { //check all values
			cout << printing(current) << endl;
			clearing();
			return 0;
		}
		if (visted[(*current).a][(*current).b] == false) { // checks for repeats in boolean array
			visted[(*current).a][(*current).b] = true;
			State *addToHolder = pour(current, 2, 0, max); //c to a
			if (check_in_holder(addToHolder) == false) { //checks for repeats in vector
				holder.push_back(addToHolder);  //adds to vector
				track.push(addToHolder); //adds to queue
			}
			else{
				delete addToHolder;
			}

			addToHolder = pour(current, 1, 0, max); //b to a
			if (check_in_holder(addToHolder) == false) {
				holder.push_back(addToHolder);
				track.push(addToHolder);
			}
			else{
				delete addToHolder;
			}

			addToHolder = pour(current, 2, 1, max); //c to b
			if (check_in_holder(addToHolder) == false) {
				holder.push_back(addToHolder);
				track.push(addToHolder);
			}
			else{
				delete addToHolder;
			}

			addToHolder = pour(current, 0, 1, max); //a to b
			if (check_in_holder(addToHolder) == false) {
				holder.push_back(addToHolder);
				track.push(addToHolder);
			}
			else{
				delete addToHolder;
			}
			addToHolder = pour(current, 1, 2, max); //b to c
			if (check_in_holder(addToHolder) == false) {
				holder.push_back(addToHolder);
				track.push(addToHolder);
			}
			else{
				delete addToHolder;
			}
			addToHolder = pour(current, 0, 2, max); //a to c
			if(check_in_holder(addToHolder)==false){
				holder.push_back(addToHolder);
				track.push(addToHolder);
			}
			else{
				delete addToHolder;
			}
		}
		else{
			continue;
		}
	}
	if(holder.size()>0){
		clearing();
	}
	cout << "No solution." << endl;
	return 1;
}
int main(int argc, char *argv[]) {
	//USE OF ATOI LEARNED FROM C++ documentation

	if (argc != 7) { //number of aruguments check
		cerr<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<< endl;
		return 1;
	}
	int checker = 0;
	string letters = "ABC";
	for (int i = 1; i < 7; i++) {
		istringstream iss(argv[i]);
		if (!(iss >> checker) || checker < 0 || (i==3 && checker<=0)) { //checks if there ints and if there are not a negative number
			if (i < 4) {//caps
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "<< letters[i - 1] << "." << endl;
				return 1;
			} else {//goals
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug "<< letters[i - 4] << "." << endl;
				return 1;
			}
			iss.clear();
		}
	}
	int checkerCap = 0;
	int totalCap = 0;
	int totalGoal=0;
	int checkerGoal = 0;
	for (int i = 1; i < 4; i++) {// check if goal is less than cap else error
		checkerCap = atoi(argv[i]);
		totalCap += checkerCap;
		checkerGoal = atoi(argv[i + 3]);
		totalGoal += checkerGoal;
		if (checkerCap < checkerGoal) {
			cerr << "Error: Goal cannot exceed capacity of jug "<< letters[i - 1] << "." << endl;
			return 1;
		}
	}
	if (checkerCap != totalGoal) { // checks if total equal to c
		cerr<< "Error: Total gallons in goal state must be equal to the capacity of jug C."<< endl;
		return 1;
	}
	int c_a = atoi(argv[1]); //cap a
	int c_b = atoi(argv[2]); //cap b
	int c_c = atoi(argv[3]); //cap c
	int g_a = atoi(argv[4]); //goal a
	int g_b = atoi(argv[5]); //goal b
	int g_c = atoi(argv[6]); //goal c
	State* start=new State(0, 0, c_c, "Initial state."); //pointer start
	State* max =new State(c_a, c_b, c_c, ""); // pointer max
	State* goal=new State(g_a, g_b, g_c, ""); // pointer goal
	c_a += 1;
	c_b += 1;
	visted = new bool*[c_a];
	for (int i = 0; i < c_a; i++) {
		visted[i] = new bool[c_b]; //create new boolean array
		 fill(visted[i], visted[i] + c_b, false);
	}
	bfs(start, *goal, *max); //bfs
	for (int i = 0; i < c_a; i++) {
		delete[] visted[i]; //delete array
	}
	///delete all pointer and array
	delete start;
	delete max;
	delete goal;
	delete[] visted;
	return 0;
}
