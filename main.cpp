/*****************************************************************************/

/* Program 5 - Decimal to Binary Converter									 */
/*****************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Program: #5


Description of the Problem:
	Write a simulation program to simulate lines at a grocery store for a
	typical day’s business.  You will assume there are three cashier lines at
	the grocery store.  Customers will enter randomly to check out  (this is a
	time stamp in the input file) and will enter the shortest line.  If the
	lines are equal, then the first line in the queue will be selected.  Each
	transaction takes a random amount of time to complete (this also is a number
	from the input file).

Functions:
    + main() - Carry out simulation based on parameters provided and output the
    	results.
    	> Initialize parameters
    	> Run simulation
    	> Output results

 */

#include "serviceSimulator.hpp"
#include <string>
#include <iostream>

using namespace std;


int main()
{

	ServiceParms parameters;

	// The number of cashiers to be stationed
	parameters.numOfCashiers = 3;

	// The maximum number of customers per lane
	parameters.lineMax = 6;

	// The total minutes in a single day
	parameters.minInDay = 570;

	// True to read customers from file or false to generate daily customers
	parameters.readInput = true;

	// The minimum and maximum arrival time
	parameters.ArrTmMin = 1;
	parameters.ArrTmMax = 15;

	// The minimum and maximum service time
	parameters.SerTmMin = 1;
	parameters.SerTmMax = 20;

	cout << "Parameters complete" << endl;

	ServiceSimulator sim(parameters);

	sim.simulate();

	return 0;
}






