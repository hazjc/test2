#include <fstream>
#include "system.h"

System::System(int N, double displacement,double radius, double boxSize, int seed) {

        this->boxSize= boxSize;
        this->dist = std::uniform_real_distribution<double>(0, 1);
        this->displacement=displacement;
        gen = std::mt19937(seed);
        
        int nSide = static_cast<int>(boxSize/ (2*radius));

        for (int i = 0; i < nSide && disks.size() < N; ++i) {
            for (int j = 0; j < nSide && disks.size() < N; ++j) {
                disks.push_back(Disk(i * 2*radius, j * 2*radius, radius));
            }
        }
    }   

bool System::overlap(int i){
    for (int j = 0; j < disks.size(); ++j) {
        if (i!=j && disks[i].distance(disks[j]) < (disks[i].radius + disks[j].radius) ) {
            return true;
        }
    }
    return false;
}

void System::step() {
    int selected_disk = std::rand() % disks.size();
    double oldx = disks[selected_disk].x;
    double oldy = disks[selected_disk].y;
    double dx = uniform(-displacement, displacement);
    double dy = uniform(-displacement, displacement);
    this->disks[selected_disk].move(dx, dy);
    
    enforceBoundaries(disks[selected_disk]);

    if (overlap(selected_disk)){
        disks[selected_disk].x = oldx;
        disks[selected_disk].y = oldy;
    }
   
}
void System::enforceBoundaries(Disk & disk) {
    // bounce mechanic if our random move over shoots the box boundaries
    // -> prevents disks getting "stuck" on walls, easier to see with big displacement sizes
    while (disk.x < 0 || disk.x > boxSize) {
        if (disk.x < 0) disk.x = -disk.x;
        else disk.x = 2*boxSize - disk.x;
    }
    while (disk.y < 0 || disk.y > boxSize) {
        if (disk.y < 0) disk.y = -disk.y;
        else disk.y = 2*boxSize - disk.y;
    }
}

double System::uniform(double min, double max) {
    // random number between min and max using our dist generator
    return min + (max - min) * dist(gen);
}

void System::save(const std::string &filename){
    // save state of disks to file
    std::ofstream outFile(filename);
    outFile<<disks.size()<<std::endl;
    outFile<<"Comment"<<std::endl;
    for (Disk& disk : disks) {
      outFile<<"A "<<disk.x<<" "<<disk.y<<" "<<disk.radius<<std::endl;

    }
    outFile.close();
    
}