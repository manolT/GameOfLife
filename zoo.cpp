/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 966022
 * @date March, 2020
 */
#include "zoo.h"
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider() {
    Grid grid = Grid(3);
    grid(1, 0) = Cell::ALIVE;
    grid(2, 1) = Cell::ALIVE;
    grid(0, 2) = Cell::ALIVE;
    grid(1, 2) = Cell::ALIVE;
    grid(2, 2) = Cell::ALIVE;
    return grid;
}


/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino() {
    Grid grid = Grid(3);
    grid(1, 0) = Cell::ALIVE;
    grid(2, 0) = Cell::ALIVE;
    grid(0, 1) = Cell::ALIVE;
    grid(1, 1) = Cell::ALIVE;
    grid(1, 2) = Cell::ALIVE;
    return grid;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 4x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship() {
    Grid grid = Grid(5,4);
    grid(1, 0) = Cell::ALIVE;
    grid(4, 0) = Cell::ALIVE;
    grid(0, 1) = Cell::ALIVE;
    grid(0, 2) = Cell::ALIVE;
    grid(4, 2) = Cell::ALIVE;
    grid(0, 3) = Cell::ALIVE;
    grid(1, 3) = Cell::ALIVE;
    grid(2, 3) = Cell::ALIVE;
    grid(3, 3) = Cell::ALIVE;
    return grid;
}


/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string path) {
    std::ifstream ifs(path, std::ifstream::in);

    if (!ifs.is_open()) {
        throw std::runtime_error("load_ascii() : File cannot be opened.");
    }

    //read width, including multiple digit width
    char inC = ifs.get();
    std::string intermediateS = "";
    while (inC != ' ') {
        intermediateS += inC;
        inC = ifs.get();
    }
    unsigned int width = 0;
    try {
       width = std::stoi(intermediateS);
    }
    catch (std::invalid_argument const &e) {
        throw std::runtime_error("load_ascii() : Cannot parse width, invalid input argument.");
    } 
    catch (std::out_of_range const& e) {
        throw std::runtime_error("load_ascii() : Cannot parse width, out of range.");
    }

    //read height
    intermediateS = "";
    while (inC != '\n') {
        intermediateS += inC;
        inC = ifs.get();
    }
    unsigned int height = 0;
    try {
        height = std::stoi(intermediateS);
    }
    catch (std::invalid_argument const& e) {
        throw std::runtime_error("load_ascii() : Cannot parse height, invalid input argument.");
    }
    catch (std::out_of_range const& e) {
        throw std::runtime_error("load_ascii() : Cannot parse height, out of range.");
    }

    Grid grid = Grid(width, height);

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            inC = ifs.get();
            if (inC == '#') {
                grid(x, y) = Cell::ALIVE;
            }
            else if (inC == ' ') {
                grid(x, y) = Cell::DEAD;
            }
            else {
                throw std::runtime_error("load_ascii() : Character for a cell is incorrect.");
            }
        }
        inC = ifs.get();
        //allows for last new line to not be there
        if (inC != '\n' && y != height-1) {
            throw std::runtime_error("load_ascii() : Missing new line character when expected.");
        }
    }

    return grid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(std::string path, Grid grid) {
    std::ofstream ofs(path, std::ofstream::out);
    if (!ofs.is_open()) {
        throw std::runtime_error("save_ascii() : File cannot be opened.");
    }

    ofs << grid.get_width() << ' ' << grid.get_height() << '\n';
    for (unsigned int y = 0; y < grid.get_height(); y++) {
        for (unsigned int x = 0; x < grid.get_width(); x++) {
            ofs << (char)grid(x, y);
        }
        ofs << '\n';
    }

}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(std::string path) {
    std::ifstream ifs;
    ifs.open(path, std::ios::binary | std::ios::in);
    if (!ifs.is_open()) {
        throw std::runtime_error("load_binary() : File cannot be opened.");
    }

    const unsigned int sizeOfInt = 4;
    const unsigned int bitsInt = 8 * sizeOfInt;

    int height;
    ifs.read(reinterpret_cast<char *>(&height), sizeOfInt);
    int width;
    ifs.read(reinterpret_cast<char*>(&width), sizeOfInt);
    
    unsigned int bytesHolder;

    Grid grid = Grid(width, height);

    //calculate how many ints we need to read from the file
    int loops = (width * height) / bitsInt;
    if ((height * width) % bitsInt != 0) {
        loops++;
    }
    
    //each loop reads one int (4 bytes) from the file
    for (int i = 0; i < loops; i++) {

        if (ifs.eof()) {
            throw std::runtime_error("load_binary() : Unexpected end of file.");
        }

        ifs.read(reinterpret_cast<char*>(&bytesHolder), sizeOfInt);
        for (unsigned int j = 0; j < sizeOfInt * 8; j++) {
            //isolating the rightmost bit in the int and then the next to the left
            unsigned int a = bytesHolder << (bitsInt - 1 - j);
            a = a >> (bitsInt - 1);
            if (a == 1) {
                //calculating the x and y coordinates based on which element we are at
                int x = ((i * sizeOfInt * 8) + j) % width;
                int y = ((i * sizeOfInt * 8) + j) / width;

                grid(x, y) = Cell::ALIVE;
            }
        }

    }
    ifs.close();
    return grid;
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(std::string path, Grid grid) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("load_binary() : File cannot be opened.");
    }

    int width = grid.get_width();
    int height = grid.get_height();

    ofs.write((char*)&width, sizeof(int));
    ofs.write((char*)&height, sizeof(int));

    //calculates how many 4 byte chunks we need to write
    int loops = (grid.get_width() * grid.get_height()) / 32;
    if ((grid.get_height() * grid.get_width()) % 32 != 0) {
        loops++;
    }

    //grid coordinates and out of bound control
    unsigned int x = 0;
    unsigned int y = 0;
    bool outOfBounds = false;
    if (grid.get_width() == 0) {
        outOfBounds = true;
    }
    unsigned int bufferInt = 0;
    //each loop writes an int (4 bytes) to the file
    for (int i = 0; i < loops; i++) {
        //each loop populates a single int with proper values
        for (int j = 0; j < 32 && !outOfBounds; j++) {
            if (grid(x,y) == Cell::ALIVE && !outOfBounds) {
                bufferInt += pow(2, j);
            }
            
            //control the grid pointer
            if (x == grid.get_width() - 1) {
                if (y == grid.get_height() - 1) {
                    outOfBounds = true;
                }
                else {
                    y++;
                    x = 0;
                }
            }
            else {
                x++;
            }
        }
        ofs.write((char*)&bufferInt, 4);
        bufferInt = 0;
    }

    ofs.close();

}
