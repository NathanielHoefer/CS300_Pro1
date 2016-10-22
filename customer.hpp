/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1

Class Name: Customer
	This class contains the information needed for each customer that is
		processed

Data:
	- (int) mCustNum: The order in which the customer enters
	- (int) mTimeStamp: The minute that the customer enters the store
	- (int) mServiceTime: The time taken for the cashier to service the
		customer

Constructors:
	+ Customer(int timeStamp, int serviceTime)

Accessor and Mutator Functions:
	+ int getCustNum()
	+ int getTimeStamp()
	+ int getServiceTime()
	+ void setCustNum(int custNum)
	+ void setTimeStamp(int timeStamp)
	+ void setServiceTime(int serviceTime)

 */

#ifndef CUSTOMER_HPP_
#define CUSTOMER_HPP_

//#include "node.hpp"
//#include <string>

using namespace std;


/*****************************************************************************/
// Class Protocol Functions and Variables
/*****************************************************************************/


class Customer
{

private:

// MEMBER VARIABLES ************************************************************

	// The order in which the customer enters
	int mCustNum;

	// The minute that the customer enters the store
	int mTimeStamp;

	// The time taken for the cashier to service the customer
	int mServiceTime;

	// The time waiting in line to be processed.
	int mWaitTime;


public:

// CONSTRUCTORS ***************************************************************

	Customer();
	Customer(int timeStamp, int serviceTime);
	Customer(int custNum, int timeStamp, int serviceTime);


// Accessors and Mutators

	int getCustNum() { return mCustNum; };
	int getTimeStamp() { return mTimeStamp; };
	int getServiceTime() { return mServiceTime; };
	void setCustNum(int custNum) { mCustNum = custNum; };
	void setTimeStamp(int timeStamp) { mTimeStamp = timeStamp; };
	void setServiceTime(int serviceTime) { mServiceTime = serviceTime; };

};


#endif /* CUSTOMER_HPP_ */
