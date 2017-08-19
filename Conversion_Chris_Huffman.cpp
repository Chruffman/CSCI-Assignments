// Chris Huffman
// Homework 7 Problem 1
// TA Upendra Sabnis


//C++ program that converts between metric and US units of length

#include <iostream>
#include <cstdlib>

using namespace std;


void inputM ( double& meters ) //input function displayed if meters to US units is chosen
{
	cout << "Enter the number of meters you would like to convert  :" << endl;
	cin >> meters;
}

void inputUS ( int& feet, double& inches )  //input function displayed if US units to meters is chosen
{
	
	cout << "Enter the number of feet and inches in the form FF II" << endl;
	cin >> feet;
	cin >> inches;
}

void convertUStoM ( int feet, double inches, double& meters )  //function containing the algorithm needed to convert US units to meters
{
	const int inches_per_foot = 12;
	const double meters_per_foot = 0.3048;
	
	if (inches < 12)
	{
		meters = meters_per_foot * ( feet + inches / inches_per_foot );
	}
	else
	{
		cout << "Please enter your inches less than 12 : " << endl;  //else statement in case input entered is outside range of accepted values
	}
	
}

void convertMtoUS ( int& feet, double& inches, double meters ) //function containing the algorithm needed to convert metric to US units
{
	const int inches_per_foot = 12;
	const double meters_per_foot = 0.3048;
	
	feet = meters / meters_per_foot;
	inches = (float (feet) / float (inches_per_foot)) - (feet / inches_per_foot); //this will assign the decimal value to inches
}

void output ( int feet, double inches, double meters ) //function that provides an output to the user
{
	
	cout << "The value of " << ' ' << feet << ' ' << "feet and " << ' ' << inches << ' ' << "inches" << ' ' << "corresponds to " << ' ' << meters << ' ' << "meters." <<endl;
}

void USToMetric() //compilation of above functions needed to convert US units to metric
{
	int feet;
	double inches, meters;
	char ans;
	do {
		inputUS(feet, inches);
		convertUStoM(feet, inches, meters);
		output(feet, inches, meters);
		cout << "Y or y continues conversion, any other character quits "
        << endl;
        cin >> ans;
	}
	while ( 'Y' == ans || 'y' == ans);
}	

void MetricToUS() //compilation of functions from above needed to convert metric to US units
{
	int feet;
	double inches;
	double meters;
	
	inputM( meters );
	
	convertMtoUS( feet, inches, meters );
	
	output( feet, inches, meters );
}

int main() //Professor Osborne's main function
{
	char ans;
	
	do
	{
		int which;
		cout << "Enter 1 for US units to Metric units or " << endl
		<< "Enter 2 for Metric units to US units conversion"
		<< endl;
		cin >> which;
		
		if ( 1 == which )
			USToMetric();
		
		else
			MetricToUS();
		
		cout << "Y or y allows another choice of conversion. "  << "any other quits." << endl;
		cin >> ans;
	}
	while ( 'y' == ans || 'Y' == ans );
	
	cout << "All done."  << endl;

	return 0;
}
