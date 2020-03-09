/**
* @author Dr. Joss Whittle
* @date March, 2020
*/

#include <iostream>

#include "grid.h"
#include "world.h"
#include "zoo.h"

int main(int argc, char *argv[]) {

    // Start with an empty grid
    Grid grid(32, 10);

    Grid glider    = Zoo::glider(),
         glider90  = glider.rotate(1),
         glider180 = glider.rotate(2),
         glider270 = glider.rotate(3);

    // Place gliders in the 4 corners all flying towards the centre
    grid.merge(glider, 1, 1, true);

    grid.merge(glider90, ((grid.get_width() - 1) - glider90.get_width()), 1, true);

    grid.merge(glider180, ((grid.get_width() - 1) - glider180.get_width()),
            ((grid.get_height() - 1) - glider180.get_height()), true);

    grid.merge(glider270, 1, ((grid.get_height() - 1) - glider180.get_height()), true);

    // Place an r-pentomino (little shape that explodes huge) in the centre of the grid.
    grid.merge(Zoo::r_pentomino(), (grid.get_width() / 2), (grid.get_height() / 2), true);

    // Print the initial state of the grid
    std::cout << grid << std::endl;

    // Save the grid to a file
    try {
        Zoo::save_ascii("output.gol", grid);
        Zoo::save_binary("output.bgol", grid);
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        std::exit(-1);
    }

    // Destructors handle all the memory deallocation
    return 0;
}
