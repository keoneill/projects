// Kevin O'Neill keoneill
// This program uses Simpson's rule to evaluate an integral. 

#include <iostream>
#include "math.h"
#include "string.h"

using namespace std;

double simRule(double a, double b, double n);
double f(double x);

int main()
{
	string function = "x^2 + 2x + 3";
	int a; // lower limit
	int b; // upper limit
	int n; // number of intervals
	
	//cout << "Enter a function: " << endl;
	//getline(cin, function);
	cout << "Enter a lower limit, a: " << endl;
	cin >> a;
	cout << "Enter an upper limit, b: " << endl;
	cin >> b;
	cout << "Enter number of intervals, n (must be even number): " << endl;
	cin >> n;

	cout << simRule(a, b, n) << endl;
	
	return 0;
}

double f(double x)
{
	return pow(x, 2) + 2 * x + 3;
}

double simRule(double a, double b, double n)
{
	double interval = (b - a) / n;
	double x = a;
	double deltaXoverThree = ((b - a)/ n) / 3;
	double ans = 0;

// loop to evaluate function at each interval	
	for (int i = 0; i <= n; i++)
	{
		if (i == 0)
		{
			ans = ans + f(a);
			x = a + interval;
		}
		else if (i == n)
		{
			ans = ans + f(b);
		}
		else if (i % 2 != 0) // if i is odd multiply f(x) by 4
		{
			ans = ans + (4 * f(x));
			x = x + interval;
		}
		else if (i % 2 == 0) // if i is even multiply f(x) by 2
		{
			ans = ans + (2 * f(x));
			x = x + interval;
		}
	}
	
	return deltaXoverThree * ans;
}
