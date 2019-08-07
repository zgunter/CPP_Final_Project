// PHYS 30762 Programming in C++
// Final project -- A board game
// Board.h
// Contains square class - basic square on the chess board

#pragma once

// Forward decleration for the piece class to be used in the header file
class Pieces;

// Class called square representing each square on the 8X8 chess board
// Contains a pointer to the piece which is on the square
// and x and y positions to use in various functions
class Square {

protected:
	// Parameters 
	Pieces* piece;
	int x_position, y_position;

public:

	// Constructor and destructor
	Square();
	Square(int x, int y);
	virtual ~Square();

	// Basic function returning information about the square
	Pieces* get_Piece();
	int get_x();
	int get_y();

	// Clear the square of its existing piece
	void set_umpty();

	// Check to see if the square is occupied by a piece
	bool is_occupied();

	// Create a new piece in a given square
	void set_newPiece(Pieces* new_piece);

};
