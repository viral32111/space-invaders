// Disable warnings for automatic variable casting
#pragma warning( disable : 4244 )

// Include this source's header file
#include "ship.h"

// Include our own header files
#include "bullet.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Define the constructor for this class which takes a single argument and initalises the base class
Ship::Ship( sf::Vector2u windowSize ) : sf::CircleShape() {

	// Update the private window width & height properties
	windowWidth = windowSize.x;
	windowHeight = windowSize.y;

	// Make the base SFML shape into a 3 sided polygon (i.e., a triangle)
	this->setPointCount( 3 );

	// Set the default colour of the base SFML shape to white with no transparency
	this->setFillColor( sf::Color( 255, 255, 255, 255 ) );

}

// Define the destructor for this class
Ship::~Ship() {

	// Reset the position of the base SFML shape so it does not interfere with anything else
	this->setPosition( sf::Vector2f( 0, 0 ) );

}

// Define the shooting method for players and enemies which will return a pointer to the bullet object
Bullet* Ship::shootBullet( int direction, bool shotByPlayer ) {

	// Instansiate a new bullet, pass our position and size, along with the direction argument (i.e, up or down), then return 
	return new Bullet( this->getPosition(), this->getLocalBounds(), direction, shotByPlayer );

}