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
	Cashier* cashiers[mParms.numOfCashiers];
	for ( int i = 0; i < mParms.numOfCashiers; i++)
		cashiers[i]->setMaxInLine(mParms.lineMax);

	// Creates the lanes as queues for each customer
	Queue* lane[mParms.numOfCashiers];

	// Generates a queue of customers to enter store
	Queue* dailyCustomers = PopulateCustomers();

	// Next customer to enter store
	Customer* currentCust = dailyCustomers->GetFront();

	bool allLinesFull = true;

	// Loop until customer list is empty
	while ( !dailyCustomers->isEmpty() )
	{

		// Checks to see if it is the current time that the customer enters
		if ( currentCust->getTimeStamp() == mCurrentTime )
		{

			int shortestLineCount = mParms.lineMax;
			int shortestLine;
			int currentLineCount;

			// Checks to see if all lines are full and updates shortest line
			for ( int i = 0; i < mParms.numOfCashiers; i++ )
			{
				// Lines full == true unless one has space
				if ( !cashiers[i]->isFull() )
					allLinesFull = false;

				// Updates shortestLine to the lane with the least customers
				currentLineCount = cashiers[i]->getCustInLine();
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
				dailyCustomers->Dequeue();
				mTurnedAway++;
			}
			else
			{
				lane[shortestLine]->Enqueue( dailyCustomers->GetFront() );
			}

			dailyCustomers->Dequeue();
			currentCust = dailyCustomers->GetFront();
			allLinesFull = true;
		}


		Customer* frontCust;

		for ( int i = 0; i < mParms.numOfCashiers; i++)
		{
			// Just verifies that the current lane is not empty
			if ( !lane[i]->isEmpty() )
			{
				frontCust = lane[i]->GetFront();

				// If time limit for current customer is 0, then move on to next
				if ( cashiers[i]->getTimeLimit() == 0 )
				{
					mTotWaitTime += (mCurrentTime - frontCust->getTimeStamp());
					lane[i]->Dequeue();

					// Subtracts 1 from number of customers in line and updates
					// the new service time for next customer
					cashiers[i]->reduceCustInLine();
					cashiers[i]->setTimeLimit(
							lane[i]->GetFront()->getServiceTime() );
					mNumberServiced++;
				}
				else
				{
					// Subtracts 1 from time to service customer
					cashiers[i]->reduceTimeLimit();
				}
			}
		}

		incrementTime();
	}
}


/*****************************************************************************/


//	Generates a list of all customers to enter in a single day using the
//		parameters provided.
//		Preconditions: The parameters are valid
//		Postconditions: A queue of customers are generated
//		Returns: The pointer of the queue of customers
Queue* ServiceSimulator::PopulateCustomers()
{
	Queue* dailyCustomers = new Queue();

	Customer* ptr = Customer;
	int custNum = 1;

	// Randomly generates a time of arrival and time taken to service for each
	// customer
	int timeStamp = TimeGenerator(mParms.ArrTmMin, mParms.ArrTmMax);
	int serviceTime = TimeGenerator(mParms.SerTmMin, mParms.SerTmMax);

	// While the end of the day hasn't been reached
	do {
		// Update the current customer's info
		ptr->setCustNum(custNum);
		ptr->setTimeStamp(timeStamp);
		ptr->setServiceTime(serviceTime);

		// Put the customer into the queue
		dailyCustomers->Enqueue(ptr);

		// Generate new values for the arrival and service time
		timeStamp += TimeGenerator(mParms.ArrTmMin, mParms.ArrTmMax);
		serviceTime = TimeGenerator(mParms.SerTmMin, mParms.SerTmMax);
		custNum++;

	} while ( timeStamp <= mParms.minInDay);

	return dailyCustomers;

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
	int range = maxTime - minTime;

	return rand() % range + minTime;
}


