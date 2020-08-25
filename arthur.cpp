/*****Version 1.1***********/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(const char* filename, int& baseHP1,int& baseHP2,int& wp1,int& wp2,int& ground)
{
	ifstream in;
	in.open(filename);
	
	if (!in.good()) return 0;

	in >> baseHP1;
	in >> wp1;
	in >> baseHP2;
	in >> wp2;
	in >> ground;

	in.close();

	if (baseHP1 < 99 || baseHP1 > 999)
		return 0;
	if (wp1 < 0 || wp1 > 3)
		return 0;
	if (baseHP2 < 1 || baseHP2 > 888)
		return 0;
	if (wp2 < 0 || wp2 > 3)
		return 0;
	if (ground < 1 || ground > 999)
		return 0;

	return 1;

}

// TODO: Your code goes here

void checkHP(int& realHP) {
	if (realHP > 999) realHP = 999;
}

bool isPrime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i <= static_cast<int>(sqrt(n)); i++) {
		if (n % i == 0) return false;
	}
	return true;
}

int realHP(int baseHP, int wp, int ground) {
	int temp;
	if (wp == 0) 
		temp = baseHP / 10;
	else 
		temp = baseHP;
	if (baseHP == ground) 
		return temp * 1.1;
	else 
		return temp;
}

float combat(int baseHP1, int baseHP2, int wp1, int wp2, int ground) {
	if (baseHP1 == 999) return 1; 
	if (baseHP2 == 888) return 0; 

	bool isPaladin1 { isPrime(baseHP1) }; 
	bool isPaladin2 { isPrime(baseHP2) };
	if (isPaladin1 && isPaladin2) {
		if (baseHP1 == baseHP2) 
			return 0.50;
		else 
			return (baseHP1 > baseHP2) ? 0.99 : 0.01;
	}
	else if (isPaladin1 && !isPaladin2) {
		return 0.99;
	}
	else if (!isPaladin1 && isPaladin2) {
		return 0.01;
	}
	else {
		if (wp1 == 3) {
			int realHP1{ 2 * realHP(baseHP1, wp1, ground) };
			checkHP(realHP1);
			int realHP2{ realHP(baseHP2, wp2, ground) };
			checkHP(realHP2);
			
			float pR{};
			pR = (static_cast<float>(realHP1) - realHP2 + 999) / 2000;
			return pR;
		}
		else {
			int realHP1{ realHP(baseHP1, wp1, ground) };
			checkHP(realHP1);
			int realHP2{ realHP(baseHP2, wp2, ground) };
			checkHP(realHP2);

			float pR{};
			pR = (static_cast<float>(realHP1) - realHP2 + 999) / 2000;
			if (wp1 == 2) {
				if (pR < 0.5) pR = 0.50;
			}
			if (wp2 == 2) {
				if (pR > 0.5) pR = 0.50;
			}
			return pR;
		}
	}
}

void display(float fOut)
// display value of fOut in format of 0.XX
// no exception handled
{
	if (fOut == 1){
		cout << fOut;
	}
	else{
		char s[10];
		sprintf(s,"%.2f",fOut);
		cout << s;
	}
}


int main(int argc, char** argv)
{
	if (argc < 2) return 1;

	const char* filename = argv[1];
	cout << filename << endl;

	int baseHP1,baseHP2,wp1,wp2,ground;
	float fOut = 0.0;
	readFile(filename, baseHP1, baseHP2, wp1, wp2, ground);
	
	// TODO: Your code goes here
	fOut = combat(baseHP1, baseHP2, wp1, wp2, ground);

	display(fOut);

	return 0;
}