# gppc-2015-submission
This repository contains my submission of Speedy and weighted A* algorithms to the GPPC in 2015
# Grid-Based Path-Planning Competition (GPPC)
Found at [movingai.com/GPPC](http://movingai.com/GPPC/), the competition is an exercise in various pathfinding approaches that are compared against each other using several metrics, including speed, memory consumption, and suboptimalility. This competition is run by Nathan Sturtevant of the University of Denver.
# Speedy and weighted A* Algorithms
These algorithms were chosen to focus on a suboptimal approach to pathfinding. These approaches are much faster than optimal solutions as they reduce the need to exhaust all optimal paths along the way to their goal. As such, they have greatly improved performance at the cost of a bounded suboptimality.
# Entries
Each algorithm (Speedy and multiple variations of weighted A*) are contained in their own directories. Each directory contains a makefile that will compile the algorithm implementation along with Entry.h (a header provided by the GPPC for API calls required for the competition). Each directory also contains main.cpp, another provided by the competition that will exectute the algorithm and display metrics when invoked with various inputs
# Maps and Scenarios
The GPPC provides several examples of maps and scenarios to be tested. Maps are grids up to 2048x2048 in size, and scenarios are a list of start and goal state that the algorithm must plan for - along with some metrics to test the provided plan. These maps are generic pathfinding grids and mazes, but also contain maps from the game Warcraft 3, Starcraft 2, and Dragon Age Origins.
# Scripts
Go to the scripts/ directory and read the README. It is a crude explanation on how to get the code compiled and also some helper scripts to run some tests.
#Performance
Note that the current Makefiles do not use the -O3 flag therefore do not acheive optimal results. The code submitted to the GPPC was compiled with this flag.
# Other Entires
Also included in this repository is a collection of previous entries to the GPPC - notably some A* implementations. These were used for emperical testing and also for data to be compiled into the paper being written on this topic.
# Liscensing
This code was submitted to the GPPC 2015 as open source.
