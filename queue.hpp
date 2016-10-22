/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1


Class Name: Queue
	Queue which contains nodes that hold customer data

Data:
	- (Node*) mFront: Contains the address of the first node.
	- (Node*) mRear: Contains the address of the last node.
	- (int) mCount: The number of the nodes in queue

Constructors:
	+ Queue() - Creates an empty queue

Accessor and Mutator Functions:
	+ Node* getFrontNode()
	+ Node* getRearNode()
	+ int getCount()
	+ void setFrontNode(Customer* ptr)
	+ void setRearNode(Customer* ptr)
	+ void setCount(int count)

Functions:
	+ void Enqueue(Customer* ptr) - Adds new node to queue with entered customer
		Preconditions: None
		Postconditions: New node is at the end of the list
		> Create new node
		> Add to the end of the list
		> Update front node to new node

	+ void Dequeue() - Removes the first customer node in list
		Precoditions: List is not empty
		Postconditions: First node is removed from list and previous node is now
			first.
		> Save first node address to new pointer
		> Update front node to 2nd node
		> Delete new pointer

	+ Customer* GetFront() - Returns the customer pointer first in the queue
		Preconditions: Queue not empty
		Postconditions: Node
		Returns: Customer*

	+ Customer* GetRear() - Returns the customer pointer last in the queue
		Precoditions: Queue not empty
		Postconditions: None
		Returns: Customer*

	+ bool isEmpty() - Determines if queue is empty or not
		Preconditions: None
		Postcoditions: None
		Returns: True if queue empty, false if not empty
		> If front node is NULL, return true
		> else return false

 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include "node.hpp"
#include "customer.hpp"
#include <string>

using namespace std;


/*****************************************************************************/
// Class Protocol Functions and Variables
/*****************************************************************************/


class Queue
{

private:

// MEMBER VARIABLES ************************************************************

	// Constains the address of the first node
	Node* mFront;

	// Contains the address of the last node.
	Node* mRear;

	// The number of the nodes in queue
	int mCount;



public:

// CONSTRUCTORS ***************************************************************

	Queue();


// METHODS ********************************************************************


// Accessors and Mutators

	Node* getFrontNode() { return mFront; };
	Node* getRearNode() { return mRear; };
	int getCount() { return mCount; };
	void setFrontNode(Node* ptr) { mFront = ptr; };
	void setRearNode(Node* ptr) { mRear = ptr; };
	void setCount(int count) { mCount = count; };


// Member Functions

	// Adds new node to queue with entered customer
	void Enqueue(Customer cust);

	// Removes the first customer node in list
	void Dequeue();

	// Returns the customer pointer first in the queue
	Customer GetFront();

	// Returns the customer pointer last in the queue
	Customer GetRear();

	// Determines if queue is empty or not
	bool isEmpty();

};


#endif /* QUEUE_HPP_ */
