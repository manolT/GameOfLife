#include <iostream>
#include "grid.h"
#include "zoo.h"

int main(int argc, char* argv[]) {

	Grid grid = Zoo::glider();
	std::cout << grid << std::endl;
	grid(0, 0) = Cell::ALIVE;
	//grid.set(0, 0, Cell::ALIVE);
	std::cout << grid << std::endl;


	return 0;
}