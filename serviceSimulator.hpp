/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1


Struct Name: ServiceParms
	This structure includes the parameters to be passed to the simulator

Data:
	+ int numOfCashiers; The number of cashiers to be stationed
	+ int lineMax; The maximum number of customers per lane
	+ int minInDay; The total minutes in a single day
	+ bool readInput; True to read customers from file or false to generate
		daily customers
	+ int ArrTmMin; The minimum arrival time
	+ int ArrTmMax; The maximum arrival time
	+ int SerTmMin; The minimum service time
	+ int SerTmMax; The maximum service time



Class Name: ServiceSimulator
	This class simulates the processing of customers within a given time period
	by using queues to imitate the lines at a store. A number of cashiers is
	specified, and then a day's worth of customers are generated using specified
	parameters. The customers are then processed based on the number of minutes
	in the specified day, and the results are calculated.

Data:
	- ServiceParms mParms; The parameters entered by the user for the simulation
	- int mCurrentTime; The time of day in minutes.
	- int mNumberServiced; The number of customers serviced.
	- int mTurnedAway; The number of customers turned away from service due to
		no open lines.
	- int mTotWaitTime; The total number of minutes customers had to wait.

Constructors:
	+ ServiceSimulator(ServiceParms parms)

Accessor and Mutator Functions:
	+ ServiceParms getServParms();
	+ int getCurrentTime();
	+ int getnumberServiced();
	+ int getTurnedAway();
	+ int getTotWaitTime();
	+ void setServParms(ServiceParms parms);
	+ void setCurrentTime(int time)
	+ void setNumberServiced(int num)
	+ void setTurnedAway(int num)
	+ void setTotWaitTime(int time)

Functions:
	+ void simulate() - Carries out the service simulation based on the entered
		parameters.
		Preconditions: The parameters are valid
		Postconditions: None
		> Create Cashiers (array)
		> Populate queue of dailyCustomers
			> If readFrom file, load customers from file
			> else generate customers and save file
		> Loop until customer list is empty
			> if customer timestamp matches currentTime
				> If all queues are full
					> remove customer
					> turnedAway++
				> else
					> Add cust to the cashier with the least cust's
			> For each cashier, service customer
				> If timeLimit is reached for front customer,
					> Dequeue current cust
					> custInLine--
					> numberServiced++
					> totWaitTime += (currentTime - custTimeStamp)
				> else
					> cashiers timeLimit--
			> currentTime++

	+ Queue* PopulateCustomers() - Generates a list of all customers to enter in
		a single day using the parameters provided.
		Preconditions: The parameters are valid
		Postconditions: A queue of customers are generated
		Returns: The pointer of the queue of customers
		> Create queue to hold customers
		> Loop until latest arrival time matches minInDay
			> Generate arrival time with ArrivalTime()
			> Generate service time with ServiceTime()
			> Create customer node with arrival and service time

	+ float AveWaitTime() - Calculates the average time the customers waited
		before being serviced.
		Preconditions: None
		Postconditions: None
		Returns: mTotWaitTime / mNumServiced

	+ void OutputResults() - Prints out the results of the simulation and
		creates an output file
		Preconditions: Simulation has already been conducted.
		Postconditions: File Output.txt is created and output printed to console
		> Gather all of the info to be output
		> Create an iostream to a file and to the console.
		> Label and date the stream.
		> Output the number of customers serviced
		> Output the total number of customers turned away
		> Output the average wait time
		> Output the total wait time
		> Close streams

	- int TimeGenerator(int minTime, int maxTime) - Generates a random time
		between the min and max time entered.
		Preconditions: None
		Postconditions: None
		Returns: minTime <= time <= maxTime
		> Use random number generator to generate between min and max
		> return generated number

	- void incrementTime();
 */

#ifndef SERVICESIMULATOR_HPP_
#define SERVICESIMULATOR_HPP_

#include "queue.hpp"
#include "cashier.hpp"
#include <string>

using namespace std;


/*****************************************************************************/
// Structure Variables
/*****************************************************************************/


struct ServiceParms
{
	// The number of cashiers to be stationed
	int numOfCashiers;

	// The maximum number of customers per lane
	int lineMax;

	// The total minutes in a single day
	int minInDay;

	// True to read customers from file or false to generate daily customers
	bool readInput;

	// The minimum and maximum arrival time
	int ArrTmMin;
	int ArrTmMax;

	// The minimum and maximum service time
	int SerTmMin;
	int SerTmMax;

};


/*****************************************************************************/
// Class Protocol Functions and Variables
/*****************************************************************************/


class ServiceSimulator
{

private:

// MEMBER VARIABLES ************************************************************

	// The parameters entered by the user for the simulation
	ServiceParms mParms;

	// The time of day in minutes.
	int mCurrentTime;

	// The number of customers serviced.
	int mNumberServiced;

	// The number of customers turned away from service due to no open lines.
	int mTurnedAway;

	// The total number of minutes customers had to wait.
	int mTotWaitTime;



public:

// Constructors

	ServiceSimulator(ServiceParms parms);


// Accessors and Mutators

	ServiceParms getServParms() { return mParms; };
	int getCurrentTime() { return mCurrentTime; };
	int getnumberServiced() { return mNumberServiced; };
	int getTurnedAway() { return mTurnedAway; };
	int getTotWaitTime() { return mTotWaitTime; };
	void setServParms(ServiceParms parms) { mParms = parms; };
	void setCurrentTime(int time) { mCurrentTime = time; };
	void setNumberServiced(int num) { mNumberServiced = num; };
 	void setTurnedAway(int num) { mTurnedAway = num; };
	void setTotWaitTime(int time) { mTotWaitTime = time; };


// Functions

	// Carries out the service simulation based on the entered parameters.
	void simulate();

	// Generates a list of all customers to enter in a single day using the
	// parameters provided.
	Queue* PopulateCustomers();

	// Calculates the average time the customers waited before being serviced.
	float AveWaitTime();

	// Prints out the results of the simulation and creates an output file.
	void OutputResults();


private:

	// Generates a random time between the min and max time entered.
	int TimeGenerator(int minTime, int maxTime);

	// Increments the current time by 1
	void incrementTime() {
		mCurrentTime++;
	}
	void readInputCust(Queue& dailyCustomers);

	void processCustomer(Queue lane[], Cashier cashiers[]);

	;

};


#endif /* SERVICESIMULATOR_HPP_ */
