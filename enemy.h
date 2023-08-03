// Ensure duplications are avoided
#pragma once

// Include native libraries
#include <vector>

// Include our own header files
#include "ship.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Create the enemy class which inherits from our custom generic ship class
class Enemy : public Ship {

	// Private properties that only this class can access
	private:

		// Used for storing the enemy's lattice position
		int myRow = 0;
		int myColumn = 0;

		// Clock for timing when the enemy should move down
		sf::Clock moveDownClock;

	// Public methods and properties which can be accessed anywhere
	public:

		// The class constructor prototype
		Enemy( sf::Vector2u windowSize, int, int );

		// The prototype method for when a bullet collides with the enemy
		void doBulletHit( std::vector<Bullet*>, int* );

		// The prototype method for moving an enemy across the screen
		void moveAcrossWindow( float, sf::RectangleShape[ 4 ], int );

		// The prototype method for checking if an enemy is obstructed by another enemy
		bool isObstructed( Enemy*[ CONFIG_ENEMY_ROWS ][ CONFIG_ENEMY_COLUMNS ] );

};
