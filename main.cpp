#include <iostream>
#include <string>
// HINT: COMPLETE THE INCLUDE STATEMENT


/**
 * @brief Entry point of the program.
 *
 * This function initializes the program and manages execution.
 */
int main() {
    // number of disks
    int N = 20;
    double maxDisplacement  = 0.6;
    double dt = 0.5;
    double L = 20.0;

    // initialise the system
    System system(N, maxDisplacement,dt,L,1234);

    // total number of iterations
    int iterations = N*500;

    for (int i = 0; i < iterations; ++i) {
        // move one disk
        system.step();
        // save a configuration
        system.save("confs/conf"+std::to_string(i));
    }
    return 0;
}