#ifndef DISK_H
#define DISK_H

class Disk {
public:
    double x, y, radius;
    Disk(double x, double y, double r);

    void move(double dx, double dy);
    double distance(Disk& d);
};

#endif
