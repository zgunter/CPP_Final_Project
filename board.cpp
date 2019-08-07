// PHYS 30762 Programming in C++
// Final project -- A board game
// Board.cpp
// Cpp file to store all functions for the class square and all its inherit classes

#include <iostream>
#include <string>
#include "board.h"
#include "square.h"
#include "chess.h"


// Functions, constructor, destructors for class Board
// Constructors
Board::Board() {

	// Set up 8X8 board with their corresponding coordinates
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chessboard[i][j] = new Square(i, j);
		}
	}
}
Board* Board::board(nullptr);

// Destructor
Board::~Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete chessboard[i][j];
		}
	}
}

// Utility functions
Board* Board::get_board() {
	return board;
}

Square* Board::get_square(int x_coord, int y_coord) {
	return chessboard[x_coord][y_coord];
}

// Function to set up the board initially with all pieces for both players
void Board::setup_board() {

	// Set up the sets for player's pieces
	// Create the players
	Player player_white("W");
	Player player_black("B");
	// Kings
	chessboard[4][0]->set_newPiece(new King("W"));
	chessboard[4][7]->set_newPiece(new King("B"));
	// Queens
	chessboard[3][0]->set_newPiece(new Queen("W"));
	chessboard[3][7]->set_newPiece(new Queen("B"));
	
	// Bishops
	chessboard[2][0]->set_newPiece(new Bishop("W"));
	chessboard[5][0]->set_newPiece(new Bishop("W"));
	chessboard[2][7]->set_newPiece(new Bishop("B"));
	chessboard[5][7]->set_newPiece(new Bishop("B"));
	// Knights
	chessboard[1][0]->set_newPiece(new Knight("W"));
	chessboard[6][0]->set_newPiece(new Knight("W"));
	chessboard[1][7]->set_newPiece(new Knight("B"));
	chessboard[6][7]->set_newPiece(new Knight("B"));
	// Rooks
	chessboard[0][0]->set_newPiece(new Rook("W"));
	chessboard[7][0]->set_newPiece(new Rook("W"));
	chessboard[0][7]->set_newPiece(new Rook("B"));
	chessboard[7][7]->set_newPiece(new Rook("B"));
	// Pawns
	for (int i = 0; i < 8; i++) {
		chessboard[i][1]->set_newPiece(new Pawn("W"));
		chessboard[i][6]->set_newPiece(new Pawn("B"));
	}
	
}

// Function to print the board
void Board::print_board() {

	// Print the headers at the top, from a to h
	for (char i = 'a'; i < 'i'; i++) {
		cout << "       " << i;
	}
	cout << " " << endl;
	// Divide the rest of the board up into 8 segments, each segment contains 4 lines
	// 1st and 3rd line consists of vertical dashes which will make up the vertical lines
	// 2nd line consists of horizontal dashes making up the horizontal lines
	// 4th line consists of a mixture of vertical dashes and letters representing chess pieces

	for (int counter_1 = 0; counter_1 < 8; counter_1++) {
		// 1st line
		cout << "   |";
		for (int counter_2 = 0; counter_2 < 8; counter_2++) {
			cout << "       |";
		}
		cout << " " << endl;
		// 2nd line
		// Need to make the each square on the board look rectangular
		// Each square takes up 5 lines on the command screen vertically
		// Which is 9 characters horizontally, minusing the ones used twice by adjacent cells
		// Adding a few extra characters at the end for cosmetics, need 66 dashes overall
		cout << "  ";
		for (int counter_3 = 0; counter_3 < 67; counter_3++) {
			cout << "-";
		}
		cout << " " << endl;
		// 3rd line
		// Same as the 1st line
		cout << "   |";
		for (int counter_4 = 0; counter_4 < 8; counter_4++) {
			cout << "       |";
		}
		cout << " " << endl;
		// 4th line
		cout << counter_1 + 1 << "  ";
		for (int i = 1; i < 9; i++) {
			cout << "|  ";
			if(chessboard[i - 1][counter_1]->is_occupied() == false){
				cout << "   ";
			}
			else {
				chessboard[i - 1][counter_1]->get_Piece()->print_letter();
			}
			cout << "  ";
		}
		cout << "| " << endl;

	}
	// Print out the bottom 3 lines which are just a repeat of the previous code for 1st and 2nd line
	cout << "   |";
	for (int counter_6 = 0; counter_6 < 8; counter_6++) {
		cout << "       |";
	}
	cout << " " << endl;
	for (int counter_7 = 0; counter_7< 67; counter_7++) {
		cout << "-";
	}
	cout << " " << endl;
}

// Function to return the player's score based on pieces left on the board
int Board::player_score(Board& gameboard, string player_colour) {
	
	int value_sum = 0;
	// Look at all pieces on the board that does not belong to player 1
	// Sum up their values, then subtract from the total value of 40 (excluding the king)
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameboard.chessboard[i][j]->get_Piece() != nullptr &&
				gameboard.chessboard[i][j]->get_Piece()->get_colour() != player_colour) {
				// Exclude the value of the king
				if (gameboard.chessboard[i][j]->get_Piece()->get_piece_value() < 1000) {
					value_sum += gameboard.chessboard[i][j]->get_Piece()->get_piece_value();
				}
			}
		}
	}
	int final_score = 40 - value_sum;
	return final_score;
};

// Function to check to see if the player is in check
bool Board::check_in_check(Board& gameboard, string player_colour) {
	// Declare variables used
	bool check = false;
	string opponent_colour;
	Square* king_position = nullptr; Square* attacking_piece;
	if (player_colour == "W") { opponent_colour = "B";}
	else { opponent_colour = "W"; }
	// Find the position of the player's king
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameboard.chessboard[i][j]->get_Piece() != nullptr &&
				gameboard.chessboard[i][j]->get_Piece()->get_colour() == player_colour &&
				gameboard.chessboard[i][j]->get_Piece()->get_piece_value() == 1000) {
				king_position = gameboard.chessboard[i][j];}}}
	// Find all enemy pieces on the board, and check to see if any of them can ove to the king's position
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameboard.chessboard[i][j]->get_Piece() != nullptr &&
				gameboard.chessboard[i][j]->get_Piece()->get_colour() == opponent_colour) {
				attacking_piece = gameboard.get_square(i, j);
				if (gameboard.chessboard[i][j]->get_Piece()->move_check(*attacking_piece,
					*king_position, gameboard)) {
					check = true;}}}}
	return check;
};

bool Board::end_game_check(Board& gameboard) {
	bool end_of_game = false;

	// Sum up all the points on the board
	int value_sum = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (gameboard.chessboard[i][j]->get_Piece() != nullptr){
					value_sum += gameboard.chessboard[i][j]->get_Piece()->get_piece_value();
				}
			}
		}

	// If the values are less than 2000 -- less than 2 kings on the board == end of game
	if (value_sum < 2000) {
		end_of_game = true;
	}
	return end_of_game;
};

// Function to excute the move by clearing both squares and setting a piece to the new square
bool Board::move_piece_content(Player player_moved, Square& origin, Square& destination, Board& gameboard) {
	bool can_move = false;

	// Check to see if the selected square is umpty
	if (origin.get_Piece() == nullptr) {
		cerr << "There's nothing in that square, please select another one" << endl;
		can_move = false;
	}

	// Check to see if the piece in origin square belongs to the player
	else if (player_moved.get_player_colour() == origin.get_Piece()->get_colour()) {
		// Check if this is a valid move by the piece in the origin square
		if (origin.get_Piece()->move_check(origin, destination, gameboard)) {
			// If the destination square is umpty, the move is allowed
			if (destination.get_Piece() == nullptr) {
				can_move = true;
			}
			// Check if the destination square contains a piece which belongs to the player
			else if (player_moved.get_player_colour() != destination.get_Piece()->get_colour()) {
				can_move = true;
			}
			else {
				cerr << "You cannot capture a piece which belongs to you!" << endl;
			}
		}
		else {
			cerr << "This piece cannot make that move, try again!" << endl;
		}
	}
	else {
		cerr << "That piece does not belong to you!" << endl;
	}

	// Clear the piece content of the origin square and set up the content of the destination
	if (can_move) {
		// Free up the origin square
		destination.set_umpty();
		destination.set_newPiece(origin.get_Piece());
		origin.set_umpty();
	}


	// Check if the player is in check, if so check to see if the next move frees the king
	if (gameboard.check_in_check(gameboard, player_moved.get_player_colour()) == true) {
		string answer;
		cout << "You will be in check after making this move!" << endl;
		cout << "Are you sure you want to make this move? y/n" << endl;
		cin >> answer;
		if (answer == "n") {
			can_move = false;
		}
	}

	return can_move;
}
