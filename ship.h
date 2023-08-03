// Ensure duplications are avoided
#pragma once

// Include our own header files
#include "bullet.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Create the generic ship class which inherits from the SFML shape class
class Ship : public sf::CircleShape {

	// Define protected properties which can be accessed by inheriting classes
	protected:

		// Store the width and height of the game window for use in position calculations
		unsigned int windowWidth = 0;
		unsigned int windowHeight = 0;

	// Define public methods which can be accessed everywhere
	public:

		// Stores if the player has been hit by an enemy bullet
		bool isDead = false;

		// The class constructor prototype
		Ship( sf::Vector2u );

		// The class destructor prototype
		~Ship();

		// The prototype method to shoot a bullet
		Bullet* shootBullet( int, bool );

};