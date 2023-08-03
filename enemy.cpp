// Disable warnings for automatic variable casting
#pragma warning( disable : 4244 )

// Include native libraries
#include <vector>
#include <cmath>

// Include this source's header file
#include "enemy.h"

// Include our own header files
#include "config.h"
#include "ship.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Global variable to hold the move direction for all enemies (i.e., left or right)
int moveDirection = 1;

// Define the constructor for this class which takes a few arguments and passes it to the constructor for the base class
Enemy::Enemy( sf::Vector2u windowSize, int currentRow, int currentColumn ) : Ship( windowSize ) {

	// Update the private properties
	myRow = currentRow;
	myColumn = currentColumn;

	// Set the size of the base SFML shape using values from the configuration file
	this->setRadius( CONFIG_PLAYER_RADIUS );

	// Set the centre/pivot point to the centre of the base SFML shape to make rotations easier
	this->setOrigin( sf::Vector2f( this->getLocalBounds().width / 2, this->getLocalBounds().height / 2 ) );

	// Set the rotation of the base SFML shape to 180 degrees to flip it over
	this->setRotation( 180 );

	// Calculate the distance between each enemy starting location based on window width and max enemy count, then lower it to the nearest whole number
	double distanceOffset = floor( ( this->windowWidth - ( CONFIG_WINDOW_PADDING * 2.0 ) - ( this->getGlobalBounds().width * 2.0 ) ) / CONFIG_ENEMY_COLUMNS );

	// Set the position of the base SFML shape based on the current row, column and previously calculated offset
	this->setPosition( sf::Vector2f(
		CONFIG_WINDOW_PADDING + ( this->getGlobalBounds().width * 2.0 ) + ( distanceOffset * myColumn ),
		CONFIG_WINDOW_PADDING + ( this->getGlobalBounds().height / 2.0 ) + ( myRow * ( this->getGlobalBounds().height * 1.5 ) ) )
	);

}

// Define the method for when a bullet collides with this enemy
void Enemy::doBulletHit( std::vector<Bullet*> allBullets, int* playerScore ) {

	// Do not continue if this enemy is dead
	if ( this->isDead ) return;

	// Loop through all bullets
	for ( Bullet* bullet : allBullets ) {
		
		// Skip this bullet if it has expired
		if ( bullet->hasExpired() ) continue;

		// Skip if this bullet was shot by an enemy
		if ( bullet->wasShotByPlayer == false ) continue;

		// If the enemy intersects with a bullet...
		if ( this->getGlobalBounds().intersects( bullet->getGlobalBounds() ) ) {

			// Mark the enemy as killed and the bullet as used
			this->isDead = true;
			bullet->isUsed = true;

			// Increment the player score
			*playerScore += 10;

		}

	}

}

// Define the method for moving the enemy across the window
void Enemy::moveAcrossWindow( float speed, sf::RectangleShape borders[ 4 ], int playerScore ) {

	// Store the global bounding box of the left and right window borders
	sf::FloatRect borderLeft = borders[ 2 ].getGlobalBounds();
	sf::FloatRect borderRight = borders[ 3 ].getGlobalBounds();

	// Flip directions for all enemies if this enemy has hit a window border
	if ( this->getGlobalBounds().intersects( borderLeft ) && moveDirection == -1 ) {
		moveDirection = -moveDirection;
	} else if ( this->getGlobalBounds().intersects( borderRight ) && moveDirection == 1 ) {
		moveDirection = -moveDirection;
	}

	// Has the configured move down time elapsed?
	if ( moveDownClock.getElapsedTime().asMilliseconds() >= CONFIG_ENEMY_TIME ) {

		// Move the enemy left or right and downwards by their own height
		this->move( sf::Vector2f( ( speed + ( playerScore / 50.0 ) ) * moveDirection, this->getGlobalBounds().height ) );

		// Reset the move down timer
		moveDownClock.restart();

	// The move down time has not elapsed
	} else {

		// Just move the enemy left or right
		this->move( sf::Vector2f( ( speed + ( playerScore / 50.0 ) ) * moveDirection, 0.0 ) );
	
	}

}

// Define the method for checking if this enemy is obstructed by another enemy
bool Enemy::isObstructed( Enemy* allEnemies[ CONFIG_ENEMY_ROWS ][ CONFIG_ENEMY_COLUMNS ] ) {

	// If this enemy is on the final row then they will never be obstructed
	if ( myRow == ( CONFIG_ENEMY_ROWS - 1 ) ) return false;

	// Loop through all rows after the current one
	for ( int row = ( myRow + 1 ); row < CONFIG_ENEMY_ROWS; row++ ) {

		// Get the enemy on this iteration's row and the same column as the current enemy
		Enemy *enemy = allEnemies[ row ][ myColumn ];

		// If the enemy is not dead then there is an obstruction
		if ( !enemy->isDead ) return true;
	}

	// There is no obstruction by default
	return false;

}