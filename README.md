# Disk Simulation

## Overview

This project implements a 2D disk simulation inside of a square as its boundary. The original base code has been extended and correct to improve correctness and usability.

At each simulation step:

-   A single disk is randomly selected

-   A random displacement is chosen

-   The move is reflected off of any boundaries it overshoots

-   The move is rejected if it overlaps with another disk

-   Each configuration is saved for visualisation

The simulation is verified to run for \> 10,000 steps efficiently and without run time errors

## Main modifications

### Header reconstruction & encapsulation

-   Reconstructed the missing `disk.h` and `system.h` header files
-   Removed redundant `#include`'s in the source files

Tag: `v0.1-headers`

### Simulation fixes

-   Implemented `Disk::distance()` correctly using euclidean distance

-   Implemented `System::uniform()` to generate a random number in a given range

-   Corrected `System::step()` so that exactly one disk move is attempted per step


Tag: `v0.2-simulation-fixed`

### Visualisation improvements

-   Fixed cross platform filename parsing

-   Improved animation smoothness (better interval between frames)

-   Added interactive playback speed slider

Tag: `v0.3-visualisation`

### CLI arguments

The program now accepts runtime parameters. They also have default values if you choose not to

```         
./sim [N] [iterations] [maxDisplacement] [dt] [L] [seed]
```

Where:

-   `N` number of disks (default: `20`)

-   `iterations` where total simulation steps = `N*iterations` (default: `500`)

-   `maxDisplacement` maximum distance of a move a disk can make at each step (default: `0.6`)

-   `dt` radius of disk (default: `0.5`)

-   `L` box size (default: `20`)

-   `seed` RNG seed (default: `1234`)

### Generalised boundary conditions

Initially, surpassing a boundary was handled by just clamping it at the wall. This however caused alot of disks to end up 'hugging' the wall especially at large displacement values. As a result I added bounce behaviour to the disks.

If a disk overshoots a boundary

-   Its position is reflected across the boundary and this is robustly applied such that it'll keep reflecting until its in bounds

-   Overlapping positions are still rejected at the end This helps disks from sticking to walls

Tag: `v1.0-final`

### Polish

-	Added a self-creating `confs/` folder in `main.cpp` so the program is self contained
-	Fixed signed and unsigned comparison warnings in `system.cpp` by casting first
-	Increased speed multiplier from a maxium of `10` to now `100` in the visualiser `view.py`
-	Removed debug `print()` messages in visualisation

Tag: `v1.1-final-polished`

## How to navigate modifications using Git

To view the full progression:

```         
git log --graph --decorate --oneline --all
```

Tagged versions:

-   `v0.1-headers`

-   `v0.2-simulation-fixed`

-   `v0.3-visualisation`

-   `v1.0-final`

-	`v1.1-final-polished`

Each tag representing a completed stage of development.

## Building the code

Compile using:

```         
g++ -std=c++17 -O2 -Wall main.cpp system.cpp disk.cpp -o sim
```

To run a simulation:

```         
./sim
```

Add arguments (if any) of your choice (See the [CLI Arguments](#cli-arguments) section for the list)

For example, a simulation with 10,000 steps:

```         
./sim 20 500
```

## Visualising results

After running the simulation run:

```         
python view.py
```

The visualiser:

-   Loads configs from `confs/`

-   Animates the disks motion in the square step by step

-   Includes an interactive slider to control playback speed
