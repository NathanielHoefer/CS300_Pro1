/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1

*/

#include "cashier.hpp"

using namespace std;

/*****************************************************************************/
// Class Source Functions
/*****************************************************************************/


// CONSTRUCTORS ***************************************************************


Cashier::Cashier()
{
	mCustInLine = 0;
	mTimeLimit = 0;
	mMaxInLine = 0;
	mIsAvailable = true;
}

Cashier::Cashier(int lineMax)
{
	mCustInLine = 0;
	mTimeLimit = 0;
	mMaxInLine = lineMax;
	mIsAvailable = true;

}


// METHODS ********************************************************************


//	Determines if the line is full.
//		Preconditions: None
//		Postconditions: None
//		Returns: True if maxInLine matches custInLine.
bool Cashier::isFull()
{
	if (mCustInLine == mMaxInLine)
		return true;
	else
		return false;
}


// Determines if the cashier is available
//		Preconditions: None
//		Postconditions: None
//		Returns: True if cashier is available to take another customer
bool Cashier::isAvailable()
{
	if ( mIsAvailable == true)
		return true;
	else
		return false;
}

