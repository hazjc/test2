#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "disk.h"

class System {
public:
    std::vector<Disk> disks;
    double boxSize;
    double displacement;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist;

    System(int N, double displacement, double radius, double boxSize, int seed);

    void step();
    
    void save(const std::string& filename);

    bool overlap(int i);

    void enforceBoundaries(Disk& disk);
    double uniform(double min, double max);
};

#endif
