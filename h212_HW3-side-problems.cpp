// All the work herein is mine <02/03/2014>
// Kevin O'Neill keoneill@indiana.edu
// I have read http://studentaffairs.iub.edu/ethics/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

const int Size = 10;
int x[Size] = {0};


// Declaration of functions
double quad(void);
int slope_intercept(void);
int substring(void);
double distance(void);
int mysterious(int x[], int Size);
int max(int x[], int Size);
int min(int x[], int Size);
int r(int *x, int Size, int vo, int vn); 

int main()
{
	cout << "Problem 1: Solve a quadractic formula. " << endl;
	quad();
	
	cout << "Problem 2: Find the equation of two points." << endl;
	slope_intercept();

	cout << "Problem 3: Is string 1 a substring of string 2? (no spaces) " << endl;
	substring();
	
	cout << "Problem 4: Find the distance between two points in three dimensions." << endl;
	distance();

	cout << "Problem 5: Mysterious!?????" << endl;
	mysterious(x, Size);

	system("pause");
	return 0;
}

// Problem 1: Function for solving a quadratic equation.
//
double quad(void)
{
	int a,b,c;
		
	cout << "Enter a value for a: " ;
	cin >> a;
	cout << "Enter a value for b: " ;
	cin >> b;
	cout << "Enter a value for c: " ;
	cin >> c;

	double numerator = b*b - 4*a*c;
	double square_root = sqrt(numerator);
	double x1 = (-b + square_root) / (2*a) ;
	double x2 = (-b - square_root) / (2*a) ;
	
	if (numerator < 0)
	{
		cout << endl;
		cout << "x1 and x2 are imaginary." << endl;
	}
	else
	{
		cout << endl;
		cout << "x1 = " << x1 << " and x2 = " << x2 << endl;
	}
	
	// Give user a choice to repeat current problem or go to the next one
	int i;
	cout << endl;
	cout << "Enter 0 to go to next problem, or 1 to repeat problem 1: " ;
	cin >> i;
	cout << endl;

	if (i == 0) 
	{
		return 0; 
	} 
	else 
	{	
		quad();
	}
	return 0;
};

// Problem 2: Function that takes two points and returns the slope-intercept equation.
//
int slope_intercept(void)
{
	double a,b,c,d;
	
	cout << "Enter two points, where p1= (a,b) p2 = (c,d) " << endl;
	cout << "a: " ;
	cin >> a;
	cout << "b: " ;
	cin >> b;
	cout << "c: " ;
	cin >> c;
	cout << "d: " ;
	cin >> d;

	double m = (d - b) / (c - a);	// finds the slope
	double bb = (m*-a) + b;			// finds the b part of y = mx + b

	cout << endl;
	cout << "y = " << m << "x " ;	// displaying the equation;
	if (bb < 0)						// if bb is less than zero than display 
	{								// the negative sign next to the absolute value of bb
		cout << "- " << abs(bb) << endl;
	}
	else							// otherwise display " + " next to the value of bb
	{
		cout << "+ " << bb << endl;
	}

	// Give user a choice to repeat current problem or go to the next one
	int i;
	cout << endl;
	cout << "Enter 0 to go to next problem, or 1 to repeat problem 2: " ;
	cin >> i;
	cout << endl;

	if (i == 0) 
	{
		return 0; 
	} 
	else 
	{	
		slope_intercept();
	}

	return 0;
}

// Problem 3: Finds whether a string is a substring of a second string.
//
int substring(void)
{
	string strSub, strMain;

	cout << "Enter string 1: " ;
	cin >> strSub; 
	cout << "Enter the string 2: " ;
	cin >> strMain; 
	cout << endl;

	bool found = 0;
	int lenSub = strSub.length();
	int lenMain = strMain.length();
	int count = 0;

	for (int i = 0; i < lenMain ; i++) // loops through the main string (str2) in which we are searching for str1
	{
		if (strMain[i] == strSub[0]) // Check if first char of str1 matches any chars in str2
		{
			for (int j = 0; i+j < lenMain; j++) //If it matches, check if the rest of str1 matches
			{
				if (strMain[i + j] == strSub[j])
				{
					count++;
					if (count == lenSub)
					{
						cout << "\"" << strSub << "\" is a substring of \"" << strMain << "\"" << endl;
					}
				}
			}
		}
	}
	if (count != lenSub)
	{
		cout << "\"" << strSub << "\" is not a substring of \"" << strMain << "\"" << endl;
	}

	
	// Give user a choice to repeat current problem or go to the next one
	int i;
	cout << endl;
	cout << "Enter 0 to go to next problem, or 1 to repeat problem 3: " ;
	cin >> i;
	cout << endl;
		
	if (i == 0) 
	{
		return 0; 
	} 
	else 
	{	
		substring();
	}

	return 0;
}

// Problem 4: Find the distance between to points in three dimensions.
//
double distance(void)
{
	double x1,y1,z1,x2,y2,z2;

	cout << "Enter two points, where p1 = (x1,y1,z1); p2 = (x2,y2,z2). " << endl;
	cout << "x1: " ;
	cin >> x1; 
	cout << "y1: " ;
	cin >> y1; 
	cout << "z1: " ;
	cin >> z1; 
	cout << "x2: " ;
	cin >> x2; 
	cout << "y2: " ;
	cin >> y2; 
	cout << "z2: " ;
	cin >> z2; 
	
	double xDist = x2 - x1;
	double yDist = y2 - y1;
	double zDist = z2 - z1;

	double temp = xDist*xDist + yDist*yDist + zDist*zDist;
	double dist = sqrt(temp);

	cout << "The distance between the points is: " << dist << endl;


	// Give user a choice to repeat current problem or go to the next one
	int i;
	cout << endl;
	cout << "Enter 0 to go to next problem, or 1 to repeat problem 4: " ;
	cin >> i;
	cout << endl;
		
	if (i == 0) 
	{
		return 0; 
	} 
	else 
	{	
		distance();
	}

	return 0;
}

// Problem 5: Mysterious.
//
int mysterious(int x[], const int Size)
{
	srand(time(0));
	int m;
	
	for (int i = 0; i < Size; i++) // Assigns each element a random number
	{
		x[i] = rand() % 100;
	}

	// Print the array after assigning random numbers.
	cout << "This is the original array: " << endl;
	for (int i = 0; i < Size; i++)
		cout << i << setw(5) << x[i] << endl;

	// run the program Size times
	for (int i = 0; i < Size; i++)
	{
		m = max(x,Size);
		cout << endl;
		cout << "The max is " << m << " and the min is " << min(x, Size) << endl;
			
		if (m % 2 == 0)
		{
			r(x,Size,m,min(x,Size)+1);
		}
		else
		{
			r(x,Size,m,max(x,Size) % 2);
		}
		
		cout << "This is the new array: " << endl;
		for (int i = 0; i < Size; i++)
		{
			cout << i << setw(5) << x[i] << endl;
		}

		cout << "Not so mysterious after all! If the original number in the array is even " << endl;
		cout << "it will be replaced with a 2 in the final array -- after 'Size' iterations." << endl;
		cout << "(if it was odd it will be replaced by 1)." << endl;
		cout << endl;
	}
	
	// Give user a choice to repeat current problem or go to the next one
	int i;
	cout << endl;
	cout << "Enter 0 to end, or 1 to repeat problem 5: " ;
	cin >> i;
	cout << endl;
		
	if (i == 0) 
	{
		return 0; 
	} 
	else 
	{	
		mysterious(x, Size);
	}

	return 0;
}

int max(int x[], int Size)
{
	int temp = 0;
	
	for (int i = 0; i < Size; i++)
	{
		if (x[i] > temp)
		{
			temp = x[i];
		}
	}
	return temp;
}
int min(int x[], int Size)
{
	int temp = x[0];
	
	for (int i = 0; i < Size; i++)
	{
		if (temp > x[i])
		{
			temp = x[i];
		}
	}
	return temp;
}
int r(int x[], int Size, int vo, int vn)
{
	for (int i = 0; i < Size; i++)
	{
		if (x[i] == vo)
		{
			x[i] = vn;
		}
	}

	return 0;
}