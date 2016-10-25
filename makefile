DIR1=-I./Source 
DIR2=-I./Header

INCLUDE = -I./Source 
INCLUDE = -I./Header


grocery: cashier.cpp customer.cpp main.cpp node.cpp queue.cpp serviceSimulator.cpp cashier.hpp customer.hpp queue.hpp serviceSimulator.hpp
	g++ -Wall cashier.cpp customer.cpp main.cpp node.cpp queue.cpp serviceSimulator.cpp -o grocery
	./grocery