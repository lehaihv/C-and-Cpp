//============================================================================
// Name        : Chap1.cpp
// Author      : Hai
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// fahren.cpp
// demonstrates cin, newline
#include <iostream>
using namespace std;
int main()
	{
	int ftemp; //for temperature in fahrenheit
	cout << "Enter temperature in fahrenheit:";
	cin >> ftemp;
	int ctemp = (ftemp-32) * 5 / 9;
	cout << "Equivalent in Celsius is: " << ctemp << '\n';
	return 0;
	}
