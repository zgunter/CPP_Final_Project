// PHYS 30762 Programming in C++
// Final project -- A board game
// Player.cpp
// Cpp file to store functions for the class player

#pragma once
#include "player.h"
using namespace std;

// For Player class
// Constructors and destructor
Player::Player() {

}
Player::Player(string colour) {
	player_colour == colour;
}
Player:: ~Player(){

}

// Utality functions
string Player::get_player_colour() {
	return player_colour;
}
void Player::set_player_colour(string colour) {
	player_colour = colour;
}

