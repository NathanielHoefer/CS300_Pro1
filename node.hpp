/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1


Class Name: Node
	This class is used for creating a node within a queue which contains the
	pointer of a customer

Data:
	- (Customer*) mCustomer: Pointer of a customer
	- (Node) *mNextNode: Pointer to next node in list

Constructors:
	+ Node() - Sets the value to default
	+ Node(Customer* cust): creates node with the arguments passed
	+ Node(Customer* cust, Node* nextNode): creates node with the arguments passed

Mutator Functions:
	+ setNextPointer
	+ setCust

Accessor Functions:
	+ getNextPointer
	+ getCust

*/

#include "customer.hpp"

using namespace std;

#ifndef NODE_HPP_
#define NODE_HPP_

class Node
{
	private:

// Member Variables

	// Pointer of a customer
	Customer* mCustomer;

	// Pointer to next node in stack
	Node *mNextNode;


	public:

// Constructors
	Node();
	Node(Customer* cust);
	Node(Customer* cust, Node* nextNode);


// Mutator and Accessor Functions
	void setNextPointer(Node *prt) { mNextNode = prt; };
	void setCust(Customer* cust) { mCustomer = cust; };
	Node * getNextPointer() { return mNextNode; };
	Customer * getCust() { return mCustomer; };

};

#endif /* NODE_HPP_ */
