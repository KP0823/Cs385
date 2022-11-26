/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Kush Parmar
 * Version     : 1.0
 * Date        :
 * Description : Implementing Karatsuba's algorithm
 * Pledge      : I pledge my honor that I have abided by the stevens honor system
 ******************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

//appends zeros to the smaller string
void fixSize(string &a,string &b ){
	if(a.size()==b.size()){
		return;
	}
	else if (a.size()>b.size()){
		int size_dif= a.size()-b.size();
		for(int i=0; i<size_dif; i++){
			b='0'+b;
		}
		return;
	}
	else{
		int size_dif= b.size()-a.size();
		for(int i=0; i<size_dif;i++){
			a='0'+a;
		}
		return;
	}
}
void mult10(string& num, int len){
	for(int i=0; i<len; i++){
		num+='0';
	}
}
string add(const string& a, const string& b){
	string new_a = a;
	string new_b = b;
	//pads zeros at beginning to make strings equal
	fixSize(new_a,new_b);
	int total;
	int carrier=0;
	string total_string;
	//adds digits, while checking if a carrier is need.
	for(int i = new_a.size()-1; i>=0;i--){
		total= (new_a[i]-'0')+(new_b[i]-'0')+carrier;
		carrier= total/10;
		total_string=to_string(total%10)+total_string;
	}
	//if there is carrier then adds it
	if(carrier>0){
		total_string= to_string(carrier)+total_string;
	}
	//deletes leading zeros
	while(total_string[0]=='0'){
		total_string.erase(0,1);
	}
	//if string is empty set it to 0
	if(total_string.size()==0){
		total_string= "0";
	}
	return total_string;
}

string subtract(const string& a, const string& b){
	string new_a=a;
	string new_b=b;
	//pads zeros at beginning to make strings equal
	fixSize(new_a,new_b);
	int total =0;
	int carrier=0;
	string total_string;
	//subtracts digits, while checking if a carrier is need.
	for(int i=new_a.size()-1;i>=0;i--){
		total= ((new_a[i]-'0')-(new_b[i]-'0')-carrier);
		if(total<0){
			total+=10;
			carrier=1;
		}
		else{
			carrier=0;
		}
		total_string=to_string(total)+total_string;
	}
	//deletes leading zeros
	while(total_string[0]=='0'){
		total_string.erase(0,1);
	}
	//if string is empty set it to 0
	if(total_string.size()==0){
		total_string= "0";
	}
	return total_string;

}
//multiplies single digit numbers
string mult (const string&a,const string&b){
	return to_string((a[0]-'0')*(b[0]-'0'));;

}
string multiply(const string&a, const string&b){
	string new_a=a;
	string new_b=b;
	//pads zeros at beginning to make strings equal
	fixSize(new_a,new_b);
	//if 1 digit then mult
	if(new_a.size()==1){
		return mult(new_a,new_b);
	}
	//pads zero at beginning to make string even length
	if(new_a.size()%2!=0){
		new_a='0'+new_a;
		new_b='0'+new_b;
	}

	//splits the string is halves
	string new_a_hf= new_a.substr(0,(new_a.size()/2));
	string new_a_hfs=new_a.substr(new_a.size()/2);
	string new_b_hf= new_b.substr(0,(new_b.size()/2));
	string new_b_hfs=new_b.substr(new_b.size()/2);

	//calls the karatsuba algorithm
	string part_one= multiply(new_a_hf,new_b_hf);
	string part_two= multiply(new_a_hfs,new_b_hfs);
	string part_three = multiply(add(new_a_hf,new_a_hfs),add(new_b_hf,new_b_hfs));
	string part_four= subtract(part_three, add(part_one,part_two));

	//pads the numbers
	mult10(part_one,new_a.size());
	mult10(part_four,(new_a.size()/2));

	//adds the numbers to make the total
	string total_string= add(add(part_one,part_two),part_four);

	//deletes leading zeros
	while(total_string[0]=='0'){
		total_string.erase(0,1);
	}
	//if string is empty set it to 0
	if(total_string.size()==0){
		total_string= "0";
	}
	return total_string;
}
int main(int argc, char* argv[]) {
	cout<<multiply(argv[1],argv[2])<<endl;
	return 0;
}
