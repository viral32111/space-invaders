// Disable warnings for automatic variable casting
#pragma warning( disable : 4244 )

// Include this source's header file
#include "player.h"

// Include our own header files
#include "config.h"
#include "ship.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Define the constructor for this class which takes a single argument and passes it to the constructor for the base class
Player::Player( sf::Vector2u windowSize ) : Ship( windowSize ) {

	// Set the size of the base SFML shape using values from the configuration file
	this->setRadius( CONFIG_PLAYER_RADIUS );

	// Set the position of the base SFML shape to the centre of the game window
	this->setPosition( sf::Vector2f(
		( this->windowWidth / 2 ) - ( this->getGlobalBounds().width / 2 ),
		this->windowHeight - this->getGlobalBounds().height - CONFIG_WINDOW_PADDING )
	);

}

// Define the method for when a bullet collides with this player
void Player::doBulletHit( std::vector<Bullet*> allBullets ) {

	// Do not continue if the player is already dead
	if ( this->isDead ) return;

	// Loop through all bullets
	for ( Bullet *bullet : allBullets ) {

		// Skip this bullet if it has expired
		if ( bullet->hasExpired() ) continue;

		// Skip if this bullet was shot by a player
		if ( bullet->wasShotByPlayer == true ) continue;

		// If the player intersects with a bullet...
		if ( this->getGlobalBounds().intersects( bullet->getGlobalBounds() ) ) {

			// Mark the player as killed and the bullet as used
			this->isDead = true;
			bullet->isUsed = true;

		}

	}

}

// Define the method for moving horizontally across the bottom of the game window
void Player::moveAcrossWindow( int horizontalOffset ) {

	// Store the position that we're trying to move to
	float horizontalPosition = this->getPosition().x + horizontalOffset;

	// Do not continue if this position is outside the bounds of the window/play area
	if ( horizontalPosition <= CONFIG_WINDOW_PADDING || horizontalPosition >= ( this->windowWidth - this->getGlobalBounds().width - CONFIG_WINDOW_PADDING ) ) return;

	// Move the base SFML shape by the stored position on the X axis
	this->move( sf::Vector2f( horizontalOffset, 0 ) );

}