/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1


Class Name: Cashier
	This class contains the information for the cashiers used to process the
		customers as they are in the front of the line.

Data:
	- int mCustInLine; the number of customers currently in the line including
		the customer being processed.
	- int mTimeLimit; The number of minutes until the customer in the front of
		the line has been processed
	- int mMaxInLine; the max number of customers in line

Constructors:
	+ Cashier()
	+ Cashier(int lineMax)

Accessor and Mutator Functions:
	+ int getCustInLine();
	+ int getTimeLimit();
	+ int getMaxInLine();
	+ void setCustInLine(int cust);
	+ void reduceCustInLine();
	+ void setTimeLimit(int timeLimit);
	+ void reduceTimeLimit();
	+ void setMaxInLine(int lineMax);

Functions:
	+ bool isFull() - Determines if the line is full.
		Preconditions: None
		Postconditions: None
		Returns: True if maxInLine matches custInLine.

 */

#ifndef CASHIER_HPP_
#define CASHIER_HPP_


using namespace std;


/*****************************************************************************/
// Class Protocol Functions and Variables
/*****************************************************************************/


class Cashier
{

private:

// MEMBER VARIABLES ************************************************************

	// The number of customers currently in the line including the customer
	// being processed.
	int mCustInLine;

	// The number of minutes until the customer in the front of the line has
	// been processed
	int mTimeLimit;

	// The max number of customers in line
	int mMaxInLine;



public:

// CONSTRUCTORS ***************************************************************

	Cashier();
	Cashier(int lineMax);


// Accessors and Mutators

	int getCustInLine() { return mCustInLine; };
	int getTimeLimit() { return mTimeLimit; };
	int getMaxInLine() { return mMaxInLine; };
	void setCustInLine(int cust) { mCustInLine = cust; };
	void reduceCustInLine() { mCustInLine--; };
	void setTimeLimit(int timeLimit) { mTimeLimit = timeLimit; };
	void reduceTimeLimit() { mTimeLimit--; };
	void setMaxInLine(int lineMax) { mMaxInLine = lineMax; };


// METHODS ********************************************************************

	// Determines if the line is full.
	bool isFull();

};


#endif /* CASHIER_HPP_ */
