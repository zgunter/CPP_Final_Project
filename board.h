// PHYS 30762 Programming in C++
// Final project -- A board game
// Board.h
// Contains board class - 8X8 square board with visualisation functions

// Make sure file is only include once in a single compilation
#pragma once
#include "square.h"
#include "player.h"

// Class board
// Contains a 2D array of square pointers - 64 to make up the chess board
// Contains a static member of the board so it can be modified globally

class Board {

protected:
	Square *chessboard[8][8];
	static Board* board;

public:
	// Constructor and destructor
	Board();
	~Board();

	// Function to return the board
	static Board* get_board();

	// Function to set up the game initially
	void setup_board();

	// Function to return a ppinter to a square
	Square* get_square(int x_coord, int y_coord);

	// Function to print the board
	void print_board();

	// Function to return the player's score based on pieces left on the board
	int player_score(Board& gameboard, string player_colour);

	// Function to check to see if the player is in check
	bool check_in_check(Board& gameboard, string opponent_colour);

	// Function to check if the game is at an end
	bool end_game_check(Board& gameboard);

	// Function to excute a move
	bool move_piece_content(Player player_moved, Square& origin, Square& destination, Board& gameboard);

};

