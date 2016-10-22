/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1

*/

#include "node.hpp"
#include "customer.hpp"
#include "queue.hpp"
#include <string>

using namespace std;

/*****************************************************************************/
// Class Source Functions
/*****************************************************************************/


// CONSTRUCTORS ***************************************************************


Queue::Queue()
{
	mFront = NULL;
	mRear = NULL;
	mCount = 0;
}


// METHODS ********************************************************************


//	Adds new node to queue with entered
//		Preconditions: None
//		Postconditions: New node is at the end of the list
void Queue::Enqueue(Customer cust)
{
	Node* newNode = new Node(cust);

	if (isEmpty())
	{
		mFront = mRear = newNode;
	}
	else
	{
		mRear->setNextPointer(newNode);
		mRear = newNode;
	}

	mCount++;
}


/*****************************************************************************/


//	Removes the first customer node in list
//		Precoditions: List is not empty
//		Postconditions: First node is removed from list and previous node is
//			now first.
void Queue::Dequeue()
{
	if (!isEmpty())
	{
		Node* ptr = mFront;

		mFront = ptr->getNextPointer();
		delete ptr;
	}
}


/*****************************************************************************/


//	Returns the customer pointer first in the queue
//		Preconditions: Queue not empty
//		Postconditions: Node
//		Returns: Customer*
Customer Queue::GetFront()
{
	return mFront->getCust();
}


/*****************************************************************************/


//	Returns the customer pointer last in the queue
//		Precoditions: Queue not empty
//		Postconditions: None
//		Returns: Customer*
Customer Queue::GetRear()
{
	return mRear->getCust();
}


/*****************************************************************************/


//	Determines if queue is empty or not
//		Preconditions: None
//		Postcoditions: None
//		Returns: True if queue empty, false if not empty
bool Queue::isEmpty()
{
	if (mFront == NULL)
		return true;
	else
		return false;
}


