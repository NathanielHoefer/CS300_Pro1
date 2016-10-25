/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1


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
    	> Run simulation which outputs results


TODO
	- Fix seed issue when generating multiple sims at once
	- Implement seconds rather than minutes to have better accuracy when
		generating
	- Include additional variables such as frequency during time of day
	- Include additional results such as generated average sales

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

	// The minimum and maximum arrival time in minutes
	parameters.arrTmMin = 1;
	parameters.arrTmMax = 5;

	// The minimum and maximum service time in minutes
	parameters.serTmMin = 1;
	parameters.serTmMax = 20;

	parameters.displayLogs = false;

	ServiceSimulator sim(parameters);

	sim.simulate();

	return 0;
}






