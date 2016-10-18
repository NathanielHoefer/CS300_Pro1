/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1

*/

#include "customer.hpp"

using namespace std;

/*****************************************************************************/
// Class Source Functions
/*****************************************************************************/


// CONSTRUCTORS ***************************************************************


Customer::Customer()
{
	mCustNum = 0;
	mTimeStamp = 0;
	mServiceTime = 0;
}


Customer::Customer(int timeStamp, int serviceTime)
{
	mCustNum = 0;
	mTimeStamp = timeStamp;
	mServiceTime = serviceTime;
}



