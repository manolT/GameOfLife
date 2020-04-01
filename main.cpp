#include <iostream>
#include "grid.h"

int main(int argc, char* argv[]) {

	unsigned int b = 0;
	unsigned int a = b << 31;
	b = a >> 31;
	std::cout << a << "//" << b << std::endl;

	return 0;
}