// Ensure duplications are avoided
#pragma once

// Include our own header files
#include "config.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Create the bullet class which inherits from a SFML shape class
class Bullet : public sf::RectangleShape {

	// Define private properties which only this class can access
	private:

		// Stores the travel speed and direction of this bullet
		int travelSpeed = 0;

		// Create an SFML clock to time how long the bullet has existed
		sf::Clock despawnClock;

	// Define public method prototypes which can be accessed everywhere
	public:

		// True or false depending on if the bullet ever hit a player or an enemy
		bool isUsed = false;

		// Stores if this bullet was shot by a player or an enemy
		bool wasShotByPlayer = true;

		// The class constructor prototype
		Bullet( sf::Vector2f, sf::FloatRect, int, bool );

		// The class destructor prototype
		~Bullet();

		// The prototype method for checking if the bullet should be removed
		bool hasExpired();

		// The prototype method for making the bullet move across the window
		void updateBulletPosition();

};