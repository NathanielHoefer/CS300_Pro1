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

	// Loop until day is completed + the max service time to account for any
	// late customers still in line
	while ( mCurrentTime < mParms.minInDay + mParms.SerTmMax)
	{

		logMsg("Time of day", mCurrentTime);

		// Checks to see if it is the current time that the customer enters
		if ( currentCust.getTimeStamp() == mCurrentTime )
		{

			logMsg("Entered store", mCurrentTime, dailyCustomers.GetFront().getCustNum(), 1);

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


//				// If only 1 customer is in the line, then update the cashier's
//				// wait time.
//				if ( cashiers[shortestLine].getCustInLine() == 1 &&
//						cashiers[shortestLine].getTimeLimit() == 0)
//				{
//					int currentSerTime = lane[shortestLine].
//											GetFront().getServiceTime();
//					cashiers[shortestLine].setTimeLimit(currentSerTime);
//
//					// Remove customer from line to be processed.
//					lane[shortestLine].Dequeue();
//					cashiers[shortestLine].reduceCustInLine();
//				}

			}

			dailyCustomers.Dequeue();

			// Only process if there are more customers for the day
			if ( !dailyCustomers.isEmpty() )
			{
				currentCust = dailyCustomers.GetFront();
			}

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

	// Randomly generates a time of arrival and time taken to service for each
	// customer
	int timeStamp = TimeGenerator(mParms.ArrTmMin, mParms.ArrTmMax);
	int serviceTime = TimeGenerator(mParms.SerTmMin, mParms.SerTmMax);


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
		timeStamp += TimeGenerator(mParms.ArrTmMin, mParms.ArrTmMax);
		serviceTime = TimeGenerator(mParms.SerTmMin, mParms.SerTmMax);
		custNum++;

	} while ( timeStamp <= mParms.minInDay);

	saveFile.close();

	cout << "File Generated" << endl;

	return dailyCustomers;
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
	cout << totWaitTime << mTotWaitTime << endl << endl;

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





void ServiceSimulator::readInputCust(Queue* dailyCustomers) {
	// Determines whether to read from file or generate file
	if (mParms.readInput)
	{
		string fileName = "customers.txt";
		ifstream readFile(fileName.c_str());
		string fileLine;

		if (readFile.is_open())
		{
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


// TODO Why is cust 9 not appearing?


void ServiceSimulator::processCustomer(Queue lane[], Cashier cashiers[])
{

	for (int i = 0; i < mParms.numOfCashiers; i++)
	{

		// If time limit for current customer is 0, then move on to next
		if ( cashiers[i].isAvailable() && !lane[i].isEmpty())
		{

			cashiers[i].setTimeLimit( lane[i].GetFront().getServiceTime() );

			logMsg("Wait time", mCurrentTime,
					lane[i].GetFront().getCustNum(),
					mCurrentTime - lane[i].GetFront().getTimeStamp());

			mTotWaitTime += (mCurrentTime -
								lane[i].GetFront().getTimeStamp());

			lane[i].Dequeue();

			// Subtracts 1 from number of customers in line and updates
			// the new service time for next customer if one in line
			cashiers[i].reduceCustInLine();

			cashiers[i].setAvailability(false);
			cashiers[i].reduceTimeLimit();

		}
		else if ( !cashiers[i].isAvailable() && lane[i].isEmpty() )
		{
			if ( cashiers[i].getTimeLimit() == 0 )
			{


				cashiers[i].setAvailability(true);
				cashiers[i].reduceCustInLine();
				mNumberServiced++;

				logMsg("Processed in lane", mCurrentTime,
						mNumberServiced, i);
			}
			else
			{
				cashiers[i].reduceTimeLimit();
			}
		}
		else if ( !cashiers[i].isAvailable() && !lane[i].isEmpty() )
		{
			if ( cashiers[i].getTimeLimit() == 0 )
			{
				cashiers[i].setTimeLimit( lane[i].GetFront().getServiceTime() );

				logMsg("Wait time", mCurrentTime,
						lane[i].GetFront().getCustNum(),
						mCurrentTime - lane[i].GetFront().getTimeStamp());

				mTotWaitTime += (mCurrentTime -
									lane[i].GetFront().getTimeStamp());

				lane[i].Dequeue();

				cashiers[i].reduceCustInLine();
				mNumberServiced++;
				cashiers[i].reduceTimeLimit();

				logMsg("Processed in lane", mCurrentTime,
						mNumberServiced, i);
			}
			else
			{
				cashiers[i].reduceTimeLimit();
			}
		}
	}
}




void ServiceSimulator::logMsg(string output, int period, int custNum, int info)
{
	if (period != 0 && custNum != 0)
		cout << "NOTE: Time " << period << ": Customer " << custNum << ": " <<
			output << " - " << info << endl;
	else
		cout << "NOTE: Time " << period << endl;
}
