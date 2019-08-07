// PHYS 30762 Programming in C++
// Final project -- A board game
// Program to give a detailed sturctured board game
// Main.cpp

#include "board.h"
#include "chess.h"
#include <iostream>
#include <vector>


// Define the limits of the board
#define x_min 'a'
#define x_max 'h'
#define y_min '1'
#define y_max '8'

// Define a few functions used in main
// Function called to display instructions to the players
void get_help() {
	cout << endl<< "Instructions" << endl;
	cout << "All pieces are displayed in capital letters" << endl;
	cout << "1st letter represent the piece, 2nd letter represent the colour of the piece. " << endl;
	cout << "Pieces including: (K)ing, (Q)ueen, (R)ook, k(N)ight, (B)ishop, (P)awn. Colours: (W)hite and (B)lack" << endl;
	cout << "The chessboard is labelled with letters (horizontally) and numbers (Vertically)" << endl;
	cout << "To move a piece, enter the position of the piece, with the letter first followed by the number." << endl;
	cout << "Enter at any stage :" << endl;
	cout << "'help' to display instructions again" << endl;
	cout << "'score' to display your current score" << endl;
	cout << "'moves' to display all the previous moves made in the game" << endl;
	cout << "'quit' to exit the game" << endl;
}

// Introduction logo
void get_intro() {
	cout << endl << endl << endl;
	cout << "        $$$$$$     $$                                                           ";
	cout << "      $$      $$   $$                                                           ";
	cout << "    $$             $$                                                           ";
	cout << "   $$              $$            $$$$       $$$$        $$$$                    ";
	cout << "   $$              $$          $$    $$   $$    $$    $$    $$	                ";
	cout << "   $$              $$ $$$     $$      $$  $$          $$                        ";
	cout << "   $$              $$    $$   $$$$$$$$$$    $$$$        $$$$                    ";
	cout << "    $$             $$     $$  $$               $$          $$                   ";
	cout << "      $$      $$   $$     $$   $$         $$    $$    $$    $$                  ";
	cout << "        $$$$$$     $$     $$     $$$$$      $$$$        $$$$                    ";
	cout << endl << "		Welcome to the chess game!" << endl << endl;
	cout << "    Made by Zhuang Gunter -- A c++ project for PHYS30762" << endl << endl;
	get_help();
	cout << endl << "                       press enter to start the game" << endl;
	cin.ignore();
}

// Function to valdate the user input as the correct format
bool validate_input(string input) {
	bool valid_input = false;
	// Check to see if the input is a special command
	if (input == "score" || input == "moves" || input == "help") {valid_input = true;}
	//Check the input is the correct length
	else if (input.size() != 2) {
		cerr << "Input is not in the correct format!" << endl;
		cerr << "Please make sure the input consists only of letters and numbers (e.g. A3, e4)!" << endl;
		cin.clear();}
	// Check input is in bound of the board
	else if (tolower(input.at(0)) < x_min || tolower(input.at(0)) > x_max ||
		tolower(input.at(1)) < y_min || tolower(input.at(1)) > y_max) {
		cerr << "Input is out of bounds!" << endl;
		cerr << "Please enter a letter between a - h, and a number between 1-8!" << endl;
		cin.clear();}
	else {
		valid_input = true;
	}
	return valid_input;
}

// Main programme
int main()
{	
	// Define variables
	// Player stats
	string name_w, name_b;
	int score = 0;
	string turn = "White";
	// Variables to contain player inputs
	string input_origin, input_destination;
	int x_origin, x_destination, y_origin, y_destination;
	Square* origin;
	Square* destination;
	// Booleans for various loops
	bool valid_move = false;
	bool end_game = false;
	bool in_check = false;
	bool loop = false;
	string loop_answer;
	// Vector to store all the moves made in a game
	string move_made;
	vector <string> moves_made;

	// Display introduction
	get_intro();

	while (loop == false) {
		// Get the players names
		cout << "Enter player1's(White) name" << endl;
		cin >> name_w;
		cin.clear();
		cout << "Enter player2's(Black) name" << endl;
		cin >> name_b;
		cin.clear();

		// Setup the game board
		Board gameboard;
		gameboard.setup_board();

		// Make the current player
		Player current_player;

		// Loop for the game using a while loop
		while (input_origin != "quit" && input_destination != "quit" && end_game == false) {

			// Display the board
			gameboard.print_board();

			// Loop for validating move using a do while loop
			do {

				// Display message showing whos turn it is
				if (turn == "White") {
					current_player.set_player_colour("W");
					cout << "It's " << name_w << "'s (White) turn:" << endl;
				}
				else {
					current_player.set_player_colour("B");
					cout << "It's " << name_b << "'s (Black) turn:" << endl;
				}

				// Check if the current player is in check
				in_check = false;
				in_check = gameboard.check_in_check(gameboard, current_player.get_player_colour());
				if (in_check) {
					cout << "YOU ARE IN CHECK!" << endl;
				}

				// Ask for the starting position
				do {
					cout << "Please select a piece to move" << endl;
					cin >> input_origin;

					if (input_origin == "help") {
						// Display help message
						get_help();
					}
					else if (input_origin == "score") {
						// Display the current player's score
						score = gameboard.player_score(gameboard, current_player.get_player_colour());
						cout << "Player's current score is " << score << endl;
					}
					else if (input_origin == "moves") {
						// Display all previous moves
						for (size_t i = 0; i < moves_made.size(); i++) {
							cout << moves_made[i] << endl;
						}
					}
					else if (input_origin == "quit") {
						// Exit program
						cout << "Thank you for playing!" << endl;
						return 0;
					}
				} while (input_origin == "help" || validate_input(input_origin) == false ||
					input_origin == "score" || input_origin == "moves");

				// Ask for destination
				do {
					cout << "Please select a square to move to:" << endl;
					cin >> input_destination;

					if (input_destination == "help") {
						// Display help message
						get_help();
					}
					else if (input_destination == "score") {
						// Display the current player's score
						score = gameboard.player_score(gameboard, current_player.get_player_colour());
						cout << "Player's current score is " << score << endl;
					}
					else if (input_destination == "moves") {
						// Display all previous moves
						for (size_t i = 0; i < moves_made.size(); i++) {
							cout << moves_made[i] << endl;
						}
					}
					else if (input_destination == "quit") {
						// Exit program
						cout << "Thank you for playing!" << endl;
						return 0;
					}
				} while (input_destination == "help" || validate_input(input_destination) == false
						|| input_destination == "moves" || input_destination == "help");

				// Move the piece in accordance to the player input
				// Use tolower and defined x/y minimums to get the needed coordinates
				// Minus x_min and y_min to get to 0 based format
				x_origin = tolower(input_origin.at(0)) - x_min; y_origin = tolower(input_origin.at(1)) - y_min;
				x_destination = tolower(input_destination.at(0)) - x_min; y_destination = tolower(input_destination.at(1)) - y_min;
				origin = gameboard.get_square(x_origin, y_origin); destination = gameboard.get_square(x_destination, y_destination);

				// Make the move
				valid_move = gameboard.move_piece_content(current_player, *origin, *destination, gameboard);
			} while (valid_move == false);

			// Store the move made in vector
			move_made = turn + ": " + input_origin + " " + input_destination;
			moves_made.push_back(move_made);	

			// Check if it is the end of the game
			end_game = gameboard.end_game_check(gameboard);
			if (end_game) {
				cout << "It's the end of the game, and the winner is " << turn << "!" << endl;
			}

			// Change turns after a sucessful move is performed
			if (turn == "White") {
				turn = "Black";
			}
			else { turn = "White"; }
		}

		// Ask the players if they would like another game
		cout << "Would you like to play another game? y/n" << endl;
		loop_answer = cin.get();
		cin.clear();
		if (loop_answer == "y") {
			loop = true;
		}
		else if (loop_answer == "n") {
			cout << "Thank you for playing!" << endl;
		}
	}
	

	return 0;
}
