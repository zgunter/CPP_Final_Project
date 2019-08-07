// PHYS 30762 Programming in C++
// Final project -- A board game
// Square.cpp
// Cpp file to store all functions for the class square

#include <iostream>
#include "square.h"
#include "chess.h"
using namespace std;

// For class Square
// Constructor and destructor
Square::Square() {
	x_position = 0; y_position = 0;
	piece = nullptr;
}

Square::Square(int x, int y) {
	x_position = x; y_position = y; 
	piece = nullptr;
}

Square::~Square() {
}

// Utility functions to return parameters of the Square class
Pieces* Square::get_Piece() {
	return piece;
}

int Square::get_x() {
	return x_position;
}

int Square::get_y() {
	return y_position;
}

// Function to clear the content of a square
void Square::set_umpty() {
	piece = nullptr;
}

// Function to check if a square is occupied or umpty
bool Square::is_occupied() {

	// Will return zero if the square is empty
	if (this->get_Piece() == nullptr) {
		return false;
	}
	return true;
}

// Function to set a new piece on a specific square
void Square::set_newPiece(Pieces* new_piece) {

	piece = new_piece;
}