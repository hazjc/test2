#include "system.h"
#include <cstdlib>
#include <exception>


/**
 * @brief Entry point of the program.
 *
 * This function initializes the program and manages execution.
 * 
 * Usage:
 * ./sim [N] [iterations] [maxDisplacement] [dt] [L] [seed]
 * 
 */
int main(int argc, char* argv[]) {
    // default parameters
    int N = 20;
    int iterations = 500;
    double maxDisplacement  = 0.6;
    double dt = 0.5;
    double L = 20.0;
    int seed = 1234;


    // parse arguments
    try {
        if (argc > 1) N = std::stoi(argv[1]);
        if (argc > 2) iterations = std::stoi(argv[2]);
        if (argc > 3) maxDisplacement = std::stod(argv[3]);
        if (argc > 4) dt = std::stod(argv[4]);
        if (argc > 5) L = std::stod(argv[5]);
        if (argc > 6) seed = std::stoi(argv[6]);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing arguments: " << e.what() << "\n";
        return 1;
    }
    // validate arguments
    if (N <= 0) {
    std::cerr << "Error: N must be positive.\n";
    return 1;
    }
    if (iterations <= 0) {
    std::cerr << "Error: iterations must be positive.\n";
    return 1;
    }
    if (maxDisplacement < 0.0) {
    std::cerr << "Error: maxDisplacement cannot be negative.\n";
    return 1;
    }
    if (dt <= 0.0) {
    std::cerr << "Error: dt must be positive.\n";
    return 1;
    }
    if (L <= 0.0) {
    std::cerr << "Error: Box size L must be positive.\n";
    return 1;
    }


    // total number of steps
    int steps = N * iterations;

    // initialise the system
    System system(N, maxDisplacement,dt,L,seed);

    for (int i = 0; i < steps; ++i) {
        // move one disk
        system.step();
        // save a configuration
        system.save("confs/conf"+std::to_string(i));
    }
    return 0;
}