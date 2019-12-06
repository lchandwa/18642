CMU 18642 - Embedded Systems Software Engineering

This repository contains the project work of the course 18642. These projects require basic knowledge of Robot Operating System and C++.

Project Description:

This project contains a greedy maze solver algorithm that makes a turtle move to that open adjacent square in the maze that has been visited the
least number of times. There are two files maze.cpp and turtle.cpp

turtle.cpp:
1. This file contains the algorithm to solve the maze, before moving forward in the maze the turtle should know which square to move to.
2. The turtle can only move 1 step at a time so to move forward it has to move to one of the adjacent sqaures in the maze.
3. The turtle can't move through the walls of the maze. So, the turtle should only consider the visit counts of the sqaures with an open path while 
   deciding its next move. Decision of next move requires storing the number of visits to each square of the maze in some form.

The turtle creates and updates a local map and records how many times it visited each square. The turtle does not know its absolute coordinates in 
the maze, but the maze is always 12 sqaures by 12 squares in size, so it is sufficient to use a 23x23 array and place the turtle in the center of 
this local map at startup. The turtle can travel at most 11 cells in any given direction from its starting point, so if the turtle's initial position
is represented in position {11,11} of the array, no matter how the turtle travels, it can keep track of its path in the array.

maze.cpp:
1. Maze knows the actual orientation and coordinates of the turtle in the maze.
2. Maze calls the bump and atend functions and supplies its results to turtle.
   bump: is true if turtle faces a wall in the maze.
   atend: is true if turtle has solved the maze and is at the end of the maze.
3. Maze calls display visits to show the number of visits of the turtle to any square of the maze. This number of visits variable is obtained from turtle.

Design Documentation:
This file contains the design details of the project.
1. Design Requirements (what the turtle.cpp is expected to do)
2. Sequence Diagrams
3. Statechart (the turtle maze solving algorithm is a state machine with 4 states: TURN_RIGHT, TURN_LEFT, MOVE_FORWARD, STOP_MOVING)
4. Traceability Matrix from Sequence Diagrams to Requirements
5. Traceability Matrix from Statechart to Requirements

Unit Testing for statechart states and transitions

test.cpp: contains unit tests with 100% transition coverage, 100% branch coverage and 100% data coverage.

Monitors

<monitor_name>_monitor.cpp: A runtime monitor is a separate ROS node that eavesdrops on all the ROS messages sent and received by the turtle. It can keep track 
of some sort of stateful turtle behavior by observing the messages. Every time a message is sent or received by the turtle, a runtime monitor receives an interrupt 
with the contents of this message and must handle the interrupt. monitor_interface.h has function declarations for these interrupt handlers.

build scripts

build.sh : builds the project and runs all unit tests

run.sh   : runs all monitors for a particular maze file (./run.sh 1 ; if you want to solve maze 1)

Maze files

There are 10 mazes m1.maze.....m10.maze that need to be solved and are solved by this project.
