// Ensure duplications are avoided
#pragma once

// Include our own header files
#include "ship.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Create the player class which inherits from our custom generic ship class
class Player : public Ship {

	// This class only has public methods
	public:

		// The class constructor prototype
		Player( sf::Vector2u windowSize );

		// The prototype method for when a bullet collides with the player
		void doBulletHit( std::vector<Bullet*> );

		// The method prototype to move the player left and right across the bottom of the window
		void moveAcrossWindow( int );

};
