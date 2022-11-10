/*******************************************************************************
 * Filename: student.cpp
 * Author  : Kush Parmar
 * Version : 1.0
 * Date    : September 13, 2022
 * Description: Creates a class called Student which includes their name, gpa, and id.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>


using namespace std;
class Student{
public:
	Student(string first,string last,float gpa,int id): first_{first}, last_{last},gpa_{gpa},id_{id} {}

	string full_name() const{
		return first_ +" "+last_;
	}
	int id()const{
		return id_;
	}
	float gpa() const{
		return gpa_;
	}
	void print_info() const
		{
			cout << full_name() << ", " << "GPA: " << setprecision(2) << fixed << gpa() << ", " << "ID: " << id() << endl;
		}

private:
	 string first_;// (type string)
	 string last_; //(type string)
	 float gpa_; //(type float)
	 int id_ ;//(type int)

};
/**
* Takes a vector of Student objects, and returns a new vector
* with all Students whose GPA is < 1.0.
*/
vector<Student> find_failing_students(const vector<Student> &students) {
	vector<Student> failing_students;
	for(auto it = students.cbegin(); it != students.cend(); it++) { // this is an iterator, cbegin()- beginning, cend-ending, i++ is not an int, auto- detects it type
		if(it->gpa()<1.0){
			failing_students.push_back(*it);
		}
	}
	return failing_students;
}
// Iterates through the students vector, appending each student whose gpa is
// less than 1.0 to the failing_students vector.

/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
 // Iterates through the students vector, calling print_info() for each student.
	for(auto it = students.cbegin();it !=students.end(); it++){
		it->print_info();
	}
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen. */
int main() {
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;
	do {
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while (gpa < 0 || gpa > 4) {
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y');
	cout << endl << "All students:" << endl;
	print_students(students);
	cout << endl << "Failing students:";
	// TODO
	// Print a space and the word 'None' on the same line if no students are failing.
	// Otherwise, print each failing student on a separate line.
	if(find_failing_students(students).size()==0){
		cout<<" None"<<endl;
	}
	else{
		cout<< endl;
		print_students(find_failing_students(students));
	}
	//students.clear();

 return 0;
}






