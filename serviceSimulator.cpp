/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1

*/

#include "serviceSimulator.hpp"
#include "queue.hpp"
#include "cashier.hpp"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

/*****************************************************************************/
// Class Source Functions
/*****************************************************************************/


// CONSTRUCTORS ***************************************************************


ServiceSimulator::ServiceSimulator(ServiceParms parms)
{
	mParms = parms;
	mCurrentTime = 1;
	mNumberServiced = 0;
	mTurnedAway = 0;
	mTotWaitTime = 0;
}



// METHODS ********************************************************************


//	Carries out the service simulation based on the entered parameters.
//		Preconditions: The parameters are valid
//		Postconditions: None
void ServiceSimulator::simulate()
{


	// Creates a number of cashiers equal to the entered parameter
	Cashier cashiers[mParms.numOfCashiers];
	for ( int i = 0; i < mParms.numOfCashiers; i++)
	{
		cashiers[i].setMaxInLine(mParms.lineMax);
	}

	// Creates the lanes as queues for each customer
	Queue lane[mParms.numOfCashiers];


	// Determines whether to read from file or generate file
	Queue dailyCustomers;
	readInputCust(&dailyCustomers);

	logMsg("Daily customers generated");

	// Next customer to enter store
	Customer currentCust = dailyCustomers.GetFront();

	bool allLinesFull = true;

	// Loop until day is completed which is 570 min per Dr. Hixon.
	while ( mCurrentTime < mParms.minInDay)
	{

		logMsg("Time of day", mCurrentTime);

		// Checks to see if it is the current time that the customer enters
		if ( currentCust.getTimeStamp() == mCurrentTime )
		{

			logMsg("Entered store", mCurrentTime,
					dailyCustomers.GetFront().getCustNum(), 1);

			// Sets line count to greatest amount or comparison
			int shortestLineCount = mParms.lineMax;
			int shortestLine;
			int currentLineCount;

			// Checks to see if all lines are full and updates shortest line
			for ( int i = 0; i < mParms.numOfCashiers; i++ )
			{
				// Lines full == true unless one has space
				if ( !cashiers[i].isFull() )
					allLinesFull = false;

				// Updates shortestLine to the lane with the least customers
				currentLineCount = cashiers[i].getCustInLine();
				if ( currentLineCount < shortestLineCount )
				{
					shortestLine = i;
					shortestLineCount = currentLineCount;
				}
			}

			// If lane is full, turn away customer, otherwise add it to the
			// shortest lane
			if ( allLinesFull )
			{
				logMsg("Turned Away", mCurrentTime,
					dailyCustomers.GetFront().getCustNum(), mTurnedAway + 1);

				dailyCustomers.Dequeue();
				mTurnedAway++;
			}
			else
			{
				lane[shortestLine].Enqueue( dailyCustomers.GetFront() );
				cashiers[shortestLine].increaseCustInLine();


				logMsg("Entered lane", mCurrentTime,
					lane[shortestLine].GetRear().getCustNum(), shortestLine);

				logMsg("Entered lane count", mCurrentTime,
						lane[shortestLine].GetRear().getCustNum(),
						lane[shortestLine].getCount());
			}

			dailyCustomers.Dequeue();

			// Only process if there are more customers for the day
			if ( !dailyCustomers.isEmpty() )
			{
				currentCust = dailyCustomers.GetFront();
			}

			// Resets the marker for all lines full
			allLinesFull = true;
		}

		// Process the customers
		processCustomer(lane, cashiers);

		incrementTime();
	}

	logMsg("Processing Finished", mCurrentTime, -1);

	OutputResults();
}


/*****************************************************************************/


//	Generates a list of all customers to enter in a single day using the
//		parameters provided.
//		Preconditions: The parameters are valid
//		Postconditions: A queue of customers are generated
//		Returns: The pointer of the queue of customers
Queue ServiceSimulator::PopulateCustomers()
{
	Queue dailyCustomers;

	int custNum = 1;
	srand(time(0));

	// Randomly generates a time of arrival and time taken to service for each
	// customer
	int timeStamp = TimeGenerator(mParms.arrTmMin, mParms.arrTmMax);
	int serviceTime = TimeGenerator(mParms.serTmMin, mParms.serTmMax);


	// Opens Text file and saves each part until inventory is complete.
	string fileName = "customers.txt";
	ofstream saveFile(fileName.c_str());

	// While the end of the day hasn't been reached
	do {

		Customer cust(custNum, timeStamp, serviceTime);

		// Put the customer into the queue
		dailyCustomers.Enqueue(cust);


		// Generates a customers file with each customer's number, time stamp
		// and service time.
		if ( !mParms.readInput )
		{

			if (saveFile.is_open())
			{
				saveFile << custNum << " " <<
							timeStamp << " " <<
							serviceTime << endl;
			}
		}

		// Generate new values for the arrival and service time
		timeStamp += TimeGenerator(mParms.arrTmMin, mParms.arrTmMax);
		serviceTime = TimeGenerator(mParms.serTmMin, mParms.serTmMax);

		custNum++;


	} while ( timeStamp <= mParms.minInDay);

	saveFile.close();

	return dailyCustomers;
}


/*****************************************************************************/


//	Read input from a file or generate a queue of daily customers
//		Precondition: File named customers.txt within the executable directory.
//		Postcondition: None
//		Returns: Queue populated with customers from txt file or generated
void ServiceSimulator::readInputCust(Queue* dailyCustomers) {

	// Determines whether to read from file or generate file
	if (mParms.readInput)
	{
		string fileName = "customers.txt";
		ifstream readFile(fileName.c_str());
		string fileLine;

		if (readFile.is_open())
		{

			// Ignores the first line since the customer count is automatically
			// calculated.
			getline(readFile, fileLine);

			// Reads each line and uses parse function to store data
			// ParseLine will return 0 if an there is an issue with opening
			// the file.
			while (getline(readFile, fileLine))
			{
				// First value of substring
				int sub1 = 0;

				// Second value of substring
				int sub2 = fileLine.find(' ');

				string custNum;
				string timeStamp;
				string serviceTime;
				int custNumVal;
				int timeStampVal;
				int serviceTimeVal;

				// customer number
				custNum = fileLine.substr(sub1, (sub2 - sub1));

				// Removes the customer number from the line
				sub1 = custNum.length() + 1;
				sub2 = fileLine.length();
				fileLine = fileLine.substr(sub1, (sub2 - sub1));

				// Parses the time stamp
				sub1 = 0;
				sub2 = fileLine.find(' ');
				timeStamp = fileLine.substr(sub1, (sub2 - sub1));

				// Parses the service time
				sub1 = timeStamp.length() + 1;
				sub2 = fileLine.length();
				serviceTime = fileLine.substr(sub1, (sub2 - sub1));

				// Converts time stamp and service time to integers
				stringstream convert1;
				convert1 << custNum;
				convert1 >> custNumVal;
				stringstream convert2;
				convert2 << timeStamp;
				convert2 >> timeStampVal;
				stringstream convert3;
				convert3 << serviceTime;
				convert3 >> serviceTimeVal;

				// Creates temp customer and adds it to the queue
				Customer temp(custNumVal, timeStampVal, serviceTimeVal);

				dailyCustomers->Enqueue(temp);
			}
		}
		readFile.close();
	} else {
		// Generates a queue of customers to enter store
		*dailyCustomers = PopulateCustomers();
	}
}


/*****************************************************************************/


// Allows the cashier to process the customers from the lane and records the
//		specific data
//		Preconditions: None
//		Postconditions: None
void ServiceSimulator::processCustomer(Queue lane[], Cashier cashiers[])
{

	for (int i = 0; i < mParms.numOfCashiers; i++)
	{

		// If cashier is available and lane has at least one customer
		if ( cashiers[i].isAvailable() && !lane[i].isEmpty())
		{
			// Display log info
			logMsg("Wait time", mCurrentTime,
						lane[i].GetFront().getCustNum(),
						mCurrentTime - lane[i].GetFront().getTimeStamp());


			// Increase the total wait time
			mTotWaitTime += (mCurrentTime - lane[i].GetFront().getTimeStamp());

			// Updates the cashiers time limit to process the current customer
			cashiers[i].setTimeLimit( lane[i].GetFront().getServiceTime() );

			// Removes the front customer from the lane to be processed
			lane[i].Dequeue();

			// Updates the cashier information
			cashiers[i].reduceCustInLine();
			cashiers[i].setAvailability(false);
			cashiers[i].reduceTimeLimit();

		}

		// If cashier is not available and lane has at least one customer
		else if ( !cashiers[i].isAvailable() && lane[i].isEmpty() )
		{

			// The cashier processes the
			if ( cashiers[i].getTimeLimit() == 0 )
			{
				// Display log info
				logMsg("Processed in lane", mCurrentTime, mNumberServiced, i);

				// Updates the cashier information
				cashiers[i].setAvailability(true);
				cashiers[i].reduceCustInLine();
				mNumberServiced++;
			}
			else
			{
				cashiers[i].reduceTimeLimit();
			}
		}

		// If cashier is not available and lane has at least one customer
		else if ( !cashiers[i].isAvailable() && !lane[i].isEmpty() )
		{
			if ( cashiers[i].getTimeLimit() == 0 )
			{
				// Display log info
				logMsg("Wait time", mCurrentTime,
						lane[i].GetFront().getCustNum(),
						mCurrentTime - lane[i].GetFront().getTimeStamp());

				mTotWaitTime += (mCurrentTime -
									lane[i].GetFront().getTimeStamp());

				cashiers[i].setTimeLimit( lane[i].GetFront().getServiceTime() );

				// Removes the front customer from the lane to be processed
				lane[i].Dequeue();

				// Display log info
				logMsg("Processed in lane", mCurrentTime, mNumberServiced, i);

				// Updates the cashier information
				cashiers[i].reduceCustInLine();
				cashiers[i].reduceTimeLimit();
				mNumberServiced++;

			}
			else
			{
				cashiers[i].reduceTimeLimit();
			}
		}
	}
}


/*****************************************************************************/


//	Prints out the results of the simulation and creates an output file
//		Preconditions: Simulation has already been conducted.
//		Postconditions: File Output.txt is created and output printed to console
void ServiceSimulator::OutputResults()
{
	string title = "Simulation results";
	string custServiced = "Total number of customers serviced: ";
	string custTurnedAway = "Total number of customers turned away: ";
	string aveWaitTime = "Average wait time: ";
	string totWaitTime = "Total wait time: ";

	string fileName = "Output.txt";

	// Opens Text file and saves each part until inventory is complete.
	ofstream saveFile(fileName.c_str());

	if (saveFile.is_open())
	{
		saveFile << title << endl << endl;
		saveFile << custServiced << mNumberServiced << endl;
		saveFile << custTurnedAway << mTurnedAway << endl;
		saveFile << aveWaitTime << AveWaitTime() << endl;
		saveFile << totWaitTime << mTotWaitTime << endl;
	}
	saveFile.close();

	cout << title << endl << endl;
	cout << custServiced << mNumberServiced << endl;
	cout << custTurnedAway << mTurnedAway << endl;
	cout << aveWaitTime << AveWaitTime() << endl;
	cout << totWaitTime << mTotWaitTime << endl;

	cout << "\nFile Saved" << endl;
}


/*****************************************************************************/


//	Calculates the average time the customers waited before being serviced.
//		Preconditions: None
//		Postconditions: None
float ServiceSimulator::AveWaitTime()
{

	return mTotWaitTime / mNumberServiced;

}


/*****************************************************************************/


//	Generates a random time between the min and max time entered.
//		Preconditions: None
//		Postconditions: None
//		Returns: minTime <= time <= maxTime
int ServiceSimulator::TimeGenerator(int minTime, int maxTime)
{
	int range = maxTime - minTime + 1;

	return rand() % range + minTime;
}


/*****************************************************************************/


// Work in progress, once completed it will create a series of generations to
//		create return more accurate results
void ServiceSimulator::SimulateSeries(ServiceSimulator parameters)
{
	ServiceSimulator sims[1000] = ServiceSimulator(parameters);
	int custServiced = 0;
	int turnedAway = 0;
	int aveWaitTime = 0;
	int totWaitTime = 0;

	for ( int i = 0; i < 1000; i++ )
	{
		cout << "Simulation " << i << endl;
		sims[i].simulate();

		custServiced += sims[i].getnumberServiced();
		turnedAway += sims[i].getTurnedAway();
		totWaitTime += sims[i].getTotWaitTime();
	}

	aveWaitTime = totWaitTime / custServiced;

	string title = "Complete Simulation results after ";
	string custServicedSt = "Total number of customers serviced: ";
	string custTurnedAway = "Total number of customers turned away: ";
	string aveWaitTimeSt = "Average wait time: ";
	string totWaitTimeSt = "Total wait time: ";

	cout << title << 1000 << " days" << endl << endl;
	cout << custServicedSt << custServiced << endl;
	cout << custTurnedAway << turnedAway << endl;
	cout << aveWaitTimeSt << aveWaitTime << endl;
	cout << totWaitTimeSt << totWaitTime << endl;
}



/*****************************************************************************/


// Display the output message, along with the time (period), the customer number
//		and an additional integer if needed
//		Preconditions: None
//		Postconditions: Log message is printed to the screen
void ServiceSimulator::logMsg(string output, int period, int custNum, int info)
{
	if ( mParms.displayLogs )
	{
		if (period != 0 && custNum != 0)
			cout << "NOTE: Time " << period << ": Customer " << custNum <<
				": " <<	output << " - " << info << endl;
		else
			cout << "NOTE: Time " << period << endl;
	}

}
