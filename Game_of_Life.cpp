/**
 * Run with -h or --help to print the usage message.
 * i.e.
 * ./Game_of_Life --help
 *
 * @author Dr. Joss Whittle
 * @date March, 2020
 */

#include <iostream>
#include <string>

// Uses cxxopts from https://github.com/jarro2783/cxxopts under the MIT license
#include "cxxopts/cxxopts.hxx"

#include "grid.h"
#include "world.h"
#include "zoo.h"

int main(int argc, char *argv[]) {

    cxxopts::Options options("Game_of_Life",
            "This program implements John Conway's Game of Life for Cellular Automaton (circa 1970).");

    // Declare the valid command line arguments and their types and default values.
    options.add_options()
            ("f,file", "Load an ascii file from the provided path.",  cxxopts::value<std::string>())
            ("o,output", "Save an ascii file to the provided path.",  cxxopts::value<std::string>())
            ("s,steps","The number of steps to simulate the world.", cxxopts::value<int>()->default_value("10"))
            ("e,every","Print world to the console every N steps. 0 disables printing.", cxxopts::value<int>()->default_value("0"))
            ("t,toroidal", "Simulate the Game of Life on a torus.", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Print usage.");

    // Actually parse the command line arguments
    auto result = options.parse(argc, argv);

    // Print the help usage for this program
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(0);
    }

    // Parse the (potentially defaulted) parameters for this simulation
    const int  steps    = result["steps"].as<int>();
    const int  every    = result["every"].as<int>();
    const bool toroidal = result["toroidal"].as<bool>();

    // Start with an empty grid
    Grid grid;

    // Attempt to read in and parse the input file as an ascii .gol file if a path was given
    if (result.count("file")) {
        try {
            grid = Zoo::load_ascii(result["file"].as<std::string>());
        }
        catch (const std::exception &ex) {
            std::cerr << ex.what() << std::endl;
            std::exit(-1);
        }
    }

    // Construct a world from the parsed grid
    World world(grid);

    // Print the initial state of the grid
    std::cout << "Initial state..." << std::endl
              << "Alive " << world.get_alive_cells() << " | Dead " << world.get_dead_cells()  << std::endl
              << world.get_state() << std::endl;

    // Perform the requested number of update steps
    for (int step = 0; step < steps; step++) {
        world.step(toroidal);

        // Print the state of the grid every N steps
        if ((every > 0) && (step % every == 0)) {
            std::cout << "Step " << (step + 1) << " of " << steps << std::endl
                      << world.get_state() << std::endl;
        }
    }

    // Print the final state of the grid
    std::cout << "Final state..." << std::endl
              << "Alive " << world.get_alive_cells() << " | Dead " << world.get_dead_cells()  << std::endl
              << world.get_state() << std::endl;

    // Attempt to save to the output directory if a path was given
    if (result.count("output")) {
        try {
            Zoo::save_ascii(result["output"].as<std::string>(), world.get_state());
        }
        catch (const std::exception &ex) {
            std::cerr << ex.what() << std::endl;
            std::exit(-1);
        }
    }

    // Destructors handle all the memory deallocation
    return 0;
}
