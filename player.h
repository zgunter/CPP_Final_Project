// PHYS 30762 Programming in C++
// Final project -- A board game
// Player.h
// Contains definition of player class

#pragma once
#include <string>
using namespace std;

// Forward decleration for class pieces to use as a parameter 
class Pieces;

// Player class
// Contains information about the colour of the pieces the player gets to controll
class Player {
protected:
	string player_colour;
public:

	// Constructor and destructors
	Player();
	Player(string colour);
	~Player();
	
	// Function to return player's colour
	string get_player_colour();

	// Function to set the player's colour
	void set_player_colour(string colour);

};

