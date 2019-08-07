// PHYS 30762 Programming in C++
// Final project -- A board game
// Chess.h
// Header file for all chess pieces derived from an abstract base class

#pragma once
#include <string>
#include <iostream>
#include "square.h"

// Forward decleration to use the board class as a parameter
class Board;

// Create abstract base class called Piece
// Base class for all pieces in the chess game

class Pieces {

protected:

	// Parameters
	std::string colour;
	int piece_value;

public:

	//Destructor
	virtual ~Pieces();

	// Function to validate the movement of various pieces -- to be overidden by each inherit class
	virtual bool move_check(Square& initial_position, Square& final_position, Board& gameboard) = 0;

	// Function to return the colour of the piece
	std::string get_colour();

	// Virtual function to print out the symbol for each piece
	void virtual print_letter();

	// Virtual function to return the score of each piece
	int get_piece_value();

	// Functions to check for a clear path between the starting positon and final position
	// Mainly used in movement check for the queen, rook and bishop

	// Check horizontally
	bool Horizontal_check(Square& start_square, Square& finish_square, Board& gameboard);
	// Check vertically
	bool Vertical_check(Square& start_square, Square& finish_square, Board& gameboard);
	// Check diagonally
	bool Diagonal_check(Square& start_square, Square& finish_square, Board& gameboard);

};

// Inherit classes for each piece
// Layout of each inherit class is the same, all of which includes constructors and destructors 
// And overridden move_check function from bass class
// Printing function included which outputs two letters, one representing the piece and one for colour

class King : public Pieces {
public:
	King(std::string player_colour);
	~King();
	bool move_check(Square& initial_position, Square& final_position, Board& gameboard) ;
	void print_letter();
};

class Queen : public Pieces {
public:
	Queen(std::string player_colour);
	~Queen();
	bool move_check(Square& initial_position, Square& final_position, Board& gameboard) ;
	void print_letter();
};

class Rook : public Pieces {
public:
	Rook(std::string player_colour);
	~Rook();
	bool move_check(Square& initial_position, Square& final_position, Board& gameboard) ;
	void print_letter();
};

class Knight : public Pieces {
public:
	Knight(std::string player_colour);
	~Knight();
	bool move_check(Square& initial_position, Square& final_position, Board& gameboard) ;
	void print_letter();
};

class Bishop : public Pieces {
public:
	Bishop(std::string player_colour);
	~Bishop();
	bool move_check(Square& initial_position, Square& final_position, Board& gameboard) ;
	void print_letter();
};

class Pawn : public Pieces {
public:
	Pawn(std::string player_colour);
	~Pawn();
	bool move_check(Square& initial_position, Square& final_position, Board& gameboard) ;
	void print_letter();
};
