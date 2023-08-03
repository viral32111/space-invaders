// Disable warnings for automatic variable casting
#pragma warning( disable : 4244 )

// Include this source's header file
#include "bullet.h"

// Include our own header files
#include "config.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Define the constructor for this class which takes a few arguments and initalises the base SFML shape class
Bullet::Bullet( sf::Vector2f shipPosition, sf::FloatRect shipBounds, int direction, bool shotByPlayer ) : sf::RectangleShape() {

	// Update the private travel speed property using the direction argument and configuration value
	travelSpeed = direction * CONFIG_BULLET_SPEED;

	// Update the public property for who shot this bullet
	wasShotByPlayer = shotByPlayer;

	// Set the default colour of the base SFML shape to white with no transparency
	this->setFillColor( sf::Color( 255, 255, 255, 255 ) );

	// Set the size of the base SFML shape using values from the configuration file
	this->setSize( sf::Vector2f( CONFIG_BULLET_WIDTH, CONFIG_BULLET_HEIGHT ) );

	// Set the position of the base SFML shape to the middle centre of the ship (check needed because enemies have a centre origin)
	if ( wasShotByPlayer ) {
		this->setPosition( sf::Vector2f( shipPosition.x + ( shipBounds.width / 2 ) - ( CONFIG_BULLET_WIDTH / 2 ), shipPosition.y ) );
	} else {
		this->setPosition( sf::Vector2f( shipPosition.x - CONFIG_BULLET_WIDTH, shipPosition.y ) );
	}

}

// Define the destructor for this class
Bullet::~Bullet() {

	// Reset the position of the base SFML shape so it does not interfere with anything else
	this->setPosition( sf::Vector2f( 0, 0 ) );

}

// Define the method for checking if the bullet should be removed
bool Bullet::hasExpired() {

	// Return true or false depending on if the private clock has elapsed passed the configured time, or if the bullet has been used
	return despawnClock.getElapsedTime().asMilliseconds() >= CONFIG_BULLET_LIFETIME || isUsed;

}

// Define the method for making the bullet move across the game window
void Bullet::updateBulletPosition() {

	// Do not continue if the bullet's lifetime has elapsed
	if ( hasExpired() ) return;

	// Move the bullet up or down using the private travel speed property
	this->move( sf::Vector2f( 0, travelSpeed ) );

}
