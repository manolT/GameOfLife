/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 966022
 * @date March, 2020
 */
#pragma once
#include "grid.h"

// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
    private:
        Grid currGrid;
        Grid nextGrid;

        unsigned int count_neighbours(const unsigned int x, const unsigned int y, 
            const bool torodial) const;

    public:
        World();
        World(const unsigned int square_size);
        World(const unsigned int width, const unsigned int height);
        World(const const Grid initial_state);

        unsigned int get_width() const;
        unsigned int get_height() const;
        unsigned int get_total_cells() const;
        unsigned int get_alive_cells() const;
        unsigned int get_dead_cells() const;
        const Grid& get_state() const;
        void resize(const unsigned int square_size);
        void resize(const unsigned int new_width, const unsigned int new_height);
        void step(const bool torodial = false);
        void advance(const unsigned int steps, const bool torodial = false);


};