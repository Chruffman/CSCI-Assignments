// Chris Huffman
// TA: Upendra Sabnis
// Homework 6

//C++ program that prints a table of decimal values along with their equivalent binary, octal, and character values


#include <iostream>  // include to allow cout / cin

using namespace std; // allow to avoid writing std:: over and over



int main(void) // call main function
{
	int i = 0;  // define variables used in program
	int bin_arr[8];
	int dec;
	int temp_dec;
	int temp_oct;
	int oct_arr[3];
	
	cout << "DEC    BINARY     OCTAL   CHAR" << endl; // first line of output showing header for the table
	for ( dec = 0; dec < 128; dec++ )  // equation setting the 'range' of the numbers to use for outputs
	{
		cout << dec << "     "; // output a space
		
		temp_dec = dec;  // define two more variables used in the following equations
		temp_oct = dec;
		
		
		for ( i = 0; i < 8; i++) // binary equation
		{
			bin_arr[i] = temp_dec % 2;
			temp_dec = temp_dec / 2;
		}
		
		for ( i = 0; i < 3; i++ ) // octal equation
		{
			oct_arr[i] = temp_oct % 8;
			temp_oct = temp_oct / 8;
		}
		
		for ( i = 7; i >= 0; i--)  // reverse and print the binary 
		{
			cout << bin_arr[i];
		}
			cout << "     ";  // more spaces
			
		for ( i = 2; i >= 0; i-- )  // reverse and print the octal
		{
			cout << oct_arr[i];
		}
		
		cout << "    ";  // space again
		cout << char(dec) << endl;  // convert and print decimals in ASCII form
	}
	return 0;
}
