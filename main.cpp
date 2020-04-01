#include <iostream>
#include "grid.h"
#include "zoo.h"

int main(int argc, char* argv[]) {

	Grid grid = Zoo::glider();
	std::cout << "what" << std::endl;
	Zoo::save_binary("./out.bgol", grid);

	return 0;
}