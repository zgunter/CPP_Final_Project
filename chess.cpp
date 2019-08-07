// PHYS 30762 Programming in C++
// Final project -- A board game
// Chess.cpp
// Cpp file for all chess pieces derived from an abstract base class

#include <iostream>
#include <string>
#include "chess.h"
#include "board.h"
using namespace std;

// For Pieces class
// Destructor
Pieces::~Pieces() { 
}

// Function to return the parameters 
string Pieces::get_colour() {
	return colour;
}

int Pieces::get_piece_value() {
	return piece_value;
}

// Function for drawing the board, print out a blank space when a square is umpty
void Pieces::print_letter() {
	cout << " ";
};

// Function to check for a clear path between 2 squares in the same row
bool Pieces::Horizontal_check(Square& start_square, Square& finish_square, Board& gameboard) {

	// To move Horizontally, both y coordinates be must be the same
	if (abs(start_square.get_y()) != abs(finish_square.get_y())) { return false;}

	else {
		// Define variables
		int dx = finish_square.get_x() - start_square.get_x();
		int y_coord = start_square.get_y();
		// Direction of iteration varies depending on the starting and end positions
		int x_direction = 1;
		if (dx < 0) { x_direction = -1; }

		// Iterate all horizontal squares between two squares
		for (int i = 1; i < abs(dx); i++) {
			if (gameboard.get_square(i*x_direction + start_square.get_x(),y_coord)
				->is_occupied()) {
				return false;
			}
		}
	}
	return true;
};

// Function to check for a clear path between 2 squares in the same column

bool Pieces::Vertical_check(Square& start_square, Square& finish_square, Board& gameboard) {

	// To move vertically, both x coordinates be must be the same
	if (abs(start_square.get_x()) != abs(finish_square.get_x())) { return false; }

	else {
		// Define variables
		int dy = finish_square.get_y() - start_square.get_y();
		int x_coord = start_square.get_x();
		// Direction of iteration varies depending on the starting and end positions
		int y_direction = 1;
		if (dy < 0) { y_direction = -1; }
		// Iterate all horizontal squares between two squares
		for (int i= 1; i < abs(dy); i++) {
			if (gameboard.get_square(x_coord,i*y_direction + start_square.get_y())
				->is_occupied()) {
				return false;
			}
		}
	}
	return true;
};

// Function to check for a clear path between 2 squares in the same diagonal
bool Pieces::Diagonal_check(Square& start_square, Square& finish_square, Board& gameboard) {

	bool check = true;
	// Compute the difference in the coordinates
	int dx = finish_square.get_x() - start_square.get_x();
	int dy = finish_square.get_y() - start_square.get_y();
	// Set up the direction of travel of the piece
	int x_direction = 1;
	int y_direction = 1;
	if (dx < 0) { x_direction = -1; }
	if (dy < 0) { y_direction = -1; }

	// Check to see if the change in x equals to the change in y
	// Cannot be a diagonal move if these are not the same
	if (abs(dx) != abs(dy)) { check = false; }

	// Iterate through all squares on this diagonal path
	if (abs(dx) == abs(dy)) {
		for (int i = 1; i < abs(dx); i++) {
			if (gameboard.get_square(i*x_direction + start_square.get_x(), i*y_direction + start_square.get_y())->is_occupied()) {
				check = false;
			}
		}
	}
	return check;
};

// Constructors, destructors and overriding functions from each inhetrit class to the piece base class

// For King class
King::King(string player_colour) {
	colour = player_colour;
	piece_value = 1000;
}

King::~King() { 
}

void King::print_letter() {
	cout << "K " << colour;
}

// Possible moves for the king:
// Moves diagonally in all directions for 1 square
bool King::move_check(Square& initial_position, Square& final_position, Board& gameboard) {

	bool can_move = false;
	int dx = abs(initial_position.get_x() - final_position.get_x());
	int dy = abs(initial_position.get_y() - final_position.get_y());
	// Moving horizontally
	if (dx == 1 && dy == 0) {
		can_move = true;
	}
	// Moving vertially
	else if (dy == 1 && dx == 0) {
		can_move = true;
	}
	// Moving diagonally
	else if (dx == 1 && dy == 1) {
			can_move = true;
	}
	return can_move;
}

// For Queen class
Queen::Queen(string player_colour) {
	colour = player_colour;
	piece_value = 10;
}

Queen::~Queen() {
}

void Queen::print_letter() {
	cout << "Q " << colour;
}

// Possible moves for the Queen
// Moves horizontally, vertically and diagonally in all directions for many squares
// As long as there are no obasticles
bool Queen::move_check(Square& initial_position, Square& final_position, Board& gameboard) {
	bool can_move = false;
	if (this->Horizontal_check(initial_position, final_position, gameboard)) {
		can_move = true;
	}
	if (this->Vertical_check(initial_position, final_position, gameboard)) {
		can_move = true;
	}
	if (this->Diagonal_check(initial_position, final_position, gameboard)) {
		can_move = true;
	}
	return can_move;
}

// For class Rook
Rook::Rook(string player_colour) {
	colour = player_colour;
	piece_value = 5;
}

Rook::~Rook() {
}

void Rook::print_letter() {
	cout << "R " << colour;
}

// Possible moves for the rook
// moves horizontally or vertically with no distance restrictions
bool Rook::move_check(Square& initial_position, Square& final_position, Board& gameboard) {
	bool can_move = false;
	if (this->Horizontal_check(initial_position, final_position, gameboard)) {
		can_move = true;
	}
	if (this->Vertical_check(initial_position, final_position, gameboard)) {
		can_move = true;
	}
	return can_move;
}

// For class Knight
Knight::Knight(string player_colour) {
	colour = player_colour;
	piece_value = 3;
}

Knight::~Knight() {
}

void Knight::print_letter() {
	cout << "N " << colour;
}

//Knights can move in an "L" shape, 2 squares vertically and 1 horizontally, and vise versa
bool Knight::move_check(Square& initial_position, Square& final_position, Board& gameboard) {

	bool can_move = false;
	// Calculate the absolute change in x and y
	int dx = abs(initial_position.get_x() - final_position.get_x());
	int dy = abs(initial_position.get_y() - final_position.get_y());
	// Knight can move is the sum of the two values equal to 3
	if (dx == 2 && dy == 1) {
		can_move = true;
	}
	if (dx == 1 && dy == 2) {
		can_move = true;
	}

	return can_move;
}

// For class Bishop
Bishop::Bishop(string player_colour) {
	colour = player_colour;
	piece_value = 3;
}

Bishop::~Bishop() {
}

void Bishop::print_letter(){
	cout << "B " << colour;
}

// Possible moves for the bishop
// Moves diagonally with no distance restrictions
bool Bishop::move_check(Square& initial_position, Square& final_position, Board& gameboard) {
	bool can_move = false;
	if (this->Diagonal_check(initial_position, final_position, gameboard)) {
		can_move = true;
	}
	return can_move;
}

// For class Pawn
Pawn::Pawn(string player_colour) {
	colour = player_colour;
	piece_value = 1;
}

Pawn::~Pawn() {
}

void Pawn::print_letter() {
	cout << "P " << colour;
}

// Possible moves for the pawn
bool Pawn::move_check(Square& initial_position, Square& final_position, Board& gameboard) {
	// Pawn can move to all 3 of its front facing squares
	// Check to see if the Pawn is black or white, and designate squares in which it can move to
	bool can_move = false;
	int dx = abs(final_position.get_x() - initial_position.get_x());
	int dy;
	// If pawn is white, it moves down the board, if its black, it moves up the board
	// Not using abs() here to prevent the piece from moving backwards
	if (colour == "W") {
		dy = final_position.get_y() - initial_position.get_y();
	}
	else {
		dy = initial_position.get_y() - final_position.get_y();
	}
	// Moving downwards on the board, hence it can move to all 3 squres below it
	if (dy == 1){
		// Can move forward vertically if the square is unoccupied
		if (dx == 0 && !final_position.is_occupied()) {
			can_move = true;
		}
		// Can move diagonally if the square is occupied
		 if (dx == 1 && final_position.is_occupied()) {
			can_move = true;
		}
	}
	// Two step advance -- Pawns can move 2 squares in its 1st turn
	if (dy == 2) {
		if (initial_position.get_y() == 6 || initial_position.get_y() == 1) {
			can_move = true;
		}
	}
	return can_move;

	// Cannot move more than 2 squares horizontally
	if (dx >= 2) {
		can_move = false;
	}
	return can_move;
}