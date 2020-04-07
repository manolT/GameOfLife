/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 966022
 * @date March, 2020
 */
#pragma once
#include <vector>
#include <iostream>

// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

    private:
        unsigned int width;
        unsigned int height;
        std::vector<Cell> gridVector;

        unsigned int get_index(const unsigned int x, const unsigned int y) const;
        unsigned int get_index_new_grid(const unsigned int x, const unsigned int y, const unsigned int newWidth) const;
        bool are_valid_coordinates(const unsigned int x, const unsigned int y) const;

    public:

        
        Grid();
        Grid(const unsigned int square_size);
        Grid(const unsigned int width, const unsigned int height);
        //const?
        unsigned int get_width() const;
        unsigned int get_height() const;
        unsigned int get_total_cells() const;
        unsigned int get_alive_cells() const;
        unsigned int get_dead_cells() const;
        void resize(const unsigned int, const unsigned int);
        void resize(const unsigned int);
        Cell get(const unsigned int x, const unsigned int y) const;
        void set(const unsigned int x, const unsigned int y, Cell cell);
        Cell operator()(const unsigned int x, const unsigned int y) const;
        Cell& operator()(const unsigned int x, const unsigned int y);
        Grid crop(const unsigned int x0, const unsigned int y0, const unsigned int x1, const unsigned int y1) const;
        void merge(const Grid other, const unsigned int x0, const unsigned int y0, const bool alive_only = false);
        Grid rotate(const int rotation) const;

        friend std::ostream& operator<<(std::ostream& lhs, const Grid& rhs);


        

};