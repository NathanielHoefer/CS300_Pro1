/*****************************************************************************/
// Project 1 - Service Simulator
/******************************************************************************
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Project: #1
*/
#include "node.hpp"
#include "customer.hpp"
#include <string>

using namespace std;

/*****************************************************************************/
// Class Source Functions
/*****************************************************************************/


// CONSTRUCTORS ***************************************************************


Node::Node()
{
	mCustomer = NULL;
	mNextNode = NULL;
}


Node::Node(Customer* cust)
{
	mCustomer = cust;
	mNextNode = NULL;
}

Node::Node(Customer* cust, Node* nextNode)
{
	mCustomer = cust;
	mNextNode = nextNode;
}

