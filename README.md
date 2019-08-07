# CPP_Final_Project
Final project for OOP using C++

The aim of this project was to implement the key features of the board game chess into a C++ programme, using concepts such as composition, inheritance and polymorphism. These concepts were demonstrated by class encapsulation using separate header files, piece class inheritance and the use of virtual functions.

Chess header and source files contains:

-abstract base class called pieces, parent class for all chess pieces 

-each individual chess piece contains its own move set and functions to check for valid movement

-virtual functions which are overriden by sub classes for movement

Square header and source files contains:

-class called square represents a square on the chess board

-pointer to a piece residing on the square, and infor about the square, e.g. coordinates, occupancy

Board header and source files contains:

-8X8 square constructor representing the chessboard

-functions to start and reset game

Main.cpp contains:

-utility functions

-loop for the programme


The final project report is also attached, including some gameplay screenshots and the debugging process.
