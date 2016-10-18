DIR1=-I./Source 
DIR2=-I./Header

INCLUDE = -I./Source 
INCLUDE = -I./Header

grocery: %.cpp %.hpp
	g++ -Wall %.cpp -o grocery
	./grocery