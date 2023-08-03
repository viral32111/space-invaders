// Disable warnings for automatic variable casting
#pragma warning( disable : 4244 )

// Include native libraries
#include <vector>
#include <random>

// Include our own header files
#include "config.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

// Include the third-party SFML library
#include "SFML/Graphics.hpp"

// Include the operating system library
#include <Windows.h>

// Global variable to track the player score and bullets shot
int playerScore = 0;
int playerBulletsShot = 0;

// Helper function to generate a random number between two numbers
int randomNumber( int minimum, int maximum ) {
	return std::rand() % ( ( maximum - minimum ) + 1 ) + minimum;
}

// The game's entry point...
int main() {

	// Setup constant variables for the screen resolution
	const unsigned int screenWidth = sf::VideoMode::getDesktopMode().width;
	const unsigned int screenHeight = sf::VideoMode::getDesktopMode().height;

	// Seed the random number generator with the current time
	std::srand( std::time( NULL ) );

	// Create a texture for the background, then import it from the configured path
	// This will automatically display an error message, then manually exit with failure code
	sf::Texture backgroundTexture;
	if ( !backgroundTexture.loadFromFile( CONFIG_WINDOW_BACKGROUND ) ) return 1;

	// Create a sprite from the imported background texture
	sf::Sprite backgroundSprite( backgroundTexture );

	// Create a font for the heads up display, and import it from the configured path
	// This will automatically display an error message, then manually exit with failure code
	sf::Font headsUpDisplayFont;
	if ( !headsUpDisplayFont.loadFromFile( CONFIG_WINDOW_FONT ) ) return 1;

	// Optionally hide the console window since a new SFML window is going to be created
	ShowWindow( GetConsoleWindow(), ( CONFIG_CONSOLE_HIDE ? SW_HIDE : SW_SHOW ) );

	// Create a base window with a width and height the same as the background texture, give it a title and prevent resizing.
	sf::RenderWindow gameWindow(
		sf::VideoMode( backgroundTexture.getSize().x, backgroundTexture.getSize().y ),
		CONFIG_WINDOW_TITLE,
		sf::Style::Titlebar | sf::Style::Close
	);

	// Optionally enable vertical syncronisation and cap the framerate
	gameWindow.setVerticalSyncEnabled( CONFIG_FRAMERATE_LOCK );
	gameWindow.setFramerateLimit( CONFIG_FRAMERATE_MAX );

	// Set the window position to the centre of the screen
	gameWindow.setPosition( sf::Vector2i(
		( screenWidth / 2 ) - ( gameWindow.getSize().x / 2 ),
		( screenHeight / 2 ) - ( gameWindow.getSize().y / 2 )
	) );

	// Create a fixed array of SFML shapes to act as the borders
	sf::RectangleShape borders[ 4 ];

	// Loop through all borders and set their color to black
	for ( int index = 0; index < 4; index++ ) borders[ index ].setFillColor( sf::Color( 0, 0, 0, 255 ) );

	// Set size and position of the top border
	borders[ 0 ].setSize( sf::Vector2f( gameWindow.getSize().x, CONFIG_WINDOW_PADDING ) );
	borders[ 0 ].setPosition( sf::Vector2f( 0, 0 ) );

	// Set size and position of the bottom border
	borders[ 1 ].setSize( sf::Vector2f( gameWindow.getSize().x, CONFIG_WINDOW_PADDING ) );
	borders[ 1 ].setPosition( sf::Vector2f( 0, gameWindow.getSize().y - CONFIG_WINDOW_PADDING ) );

	// Set size and position of the left border
	borders[ 2 ].setSize( sf::Vector2f( CONFIG_WINDOW_PADDING, gameWindow.getSize().y ) );
	borders[ 2 ].setPosition( sf::Vector2f( 0, 0 ) );

	// Set size and position of the right border
	borders[ 3 ].setSize( sf::Vector2f( CONFIG_WINDOW_PADDING, gameWindow.getSize().y ) );
	borders[ 3 ].setPosition( sf::Vector2f( gameWindow.getSize().x - CONFIG_WINDOW_PADDING, 0 ) );

	// Create a fixed array of SFML text objects
	sf::Text texts[ 3 ];

	// Loop through all the text objects and set their font, size and color to white
	for ( int index = 0; index < 3; index++ ) {
		texts[ index ].setFont( headsUpDisplayFont );
		texts[ index ].setCharacterSize( 14 );
		texts[ index ].setFillColor( sf::Color( 255, 255, 255, 255 ) );
	}

	// Setup the text for displaying the score at the bottom of the game window
	texts[ 0 ].setString( "Score: 0" );
	texts[ 0 ].setOrigin( sf::Vector2f( texts[ 0 ].getGlobalBounds().width / 2, texts[ 0 ].getGlobalBounds().height / 2 ) );
	texts[ 0 ].setPosition( sf::Vector2f( gameWindow.getSize().x / 2 - ( gameWindow.getSize().x / 4 ), gameWindow.getSize().y - 18 ) );

	// Create the text for displaying the bullets shot and place it at the bottom of the screen
	texts[ 1 ].setString( "Shots: 0" );
	texts[ 1 ].setOrigin( sf::Vector2f( texts[ 1 ].getGlobalBounds().width / 2, texts[ 1 ].getGlobalBounds().height / 2 ) );
	texts[ 1 ].setPosition( sf::Vector2f( gameWindow.getSize().x / 2 + ( gameWindow.getSize().x / 4 ), gameWindow.getSize().y - 18 ) );

	// Create the text for when the game is over and place it in the middle of the screen
	texts[ 2 ].setString( "Game Over!" ); // or 'You Win!'
	texts[ 2 ].setCharacterSize( 48 );
	texts[ 2 ].setOutlineColor( sf::Color( 0, 0, 0, 255 ) );
	texts[ 2 ].setOrigin( sf::Vector2f( texts[ 2 ].getGlobalBounds().width / 2, texts[ 2 ].getGlobalBounds().height / 2 ) );
	texts[ 2 ].setPosition( sf::Vector2f( gameWindow.getSize().x / 2, gameWindow.getSize().y - 150 ) );

	// Create a new player in heap memory
	Player* player = new Player( gameWindow.getSize() );

	// Create an empty fixed-length multi-dimensional array for holding pointers to instansiated enemies
	Enemy* allEnemies[ CONFIG_ENEMY_ROWS ][ CONFIG_ENEMY_COLUMNS ] {};

	// Loop through all slots of the multi-dimensional array
	for ( int row = 0; row < CONFIG_ENEMY_ROWS; row++ ) {
		for ( int column = 0; column < CONFIG_ENEMY_COLUMNS; column++ ) {

			// Instansiate a new enemy object and give it the current iteration values
			Enemy* enemy = new Enemy( gameWindow.getSize(), row, column );

			// Add the new enemy object pointer to the array
			allEnemies[ row ][ column ] = enemy;

		}
	}

	// Create an empty dynamic-length vector to hold the instansiated bullets
	std::vector<Bullet*> allBullets;

	// Create an SFML clock for checking the player and enemy bullet shoot cooldown later on
	sf::Clock playerShootCooldown;
	sf::Clock enemyShootCooldown;

	// Create a new event object for storing polled event data
	sf::Event eventSystem;

	// Repeat forever so long as the base window is open (main game event loop)...
	while ( gameWindow.isOpen() ) {

		// Repeat forever if any events have occured on the base window...
		while ( gameWindow.pollEvent( eventSystem ) ) {

			// Close the base window if the event is the user window attempting to close the window
			if ( eventSystem.type == sf::Event::EventType::Closed ) gameWindow.close();

		}

		// If the player is not dead
		if ( !player->isDead ) {

			// If the user is pressing the left arrow or A key then move the player to the left
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) {
				player->moveAcrossWindow( -( int ) CONFIG_PLAYER_SPEED );
			}

			// If the user is pressing the right arrow or A key then move the player to the right
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) || sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) {
				player->moveAcrossWindow( CONFIG_PLAYER_SPEED );
			}

			// If the user is pressing the up arrow key or space, and the shoot cooldown has elapsed
			if ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) && playerShootCooldown.getElapsedTime().asMilliseconds() >= CONFIG_PLAYER_COOLDOWN ) {

				// Shoot a bullet and store the newly instansiated bullet
				Bullet *bullet = player->shootBullet( -1, true );

				// Add the new bullet to the vector containing all active bullets
				allBullets.push_back( bullet );

				// Reset the shooting cooldown clock
				playerShootCooldown.restart();

				// Increment the amount of bullets shot
				playerBulletsShot++;

			}

		}

		// Clear all drawn items from the base window
		gameWindow.clear();

		// Draw the background texture as the sprite
		gameWindow.draw( backgroundSprite );

		// Run the method for when a bullet collides with the player
		player->doBulletHit( allBullets );

		// Has the player been killed by an enemy?
		if ( player->isDead ) {

			// Draw game over text
			gameWindow.draw( texts[ 2 ] );

		// The player has not been killed yet
		} else {

			// Draw the player
			gameWindow.draw( *player );

		}

		// Loop through all existing bullets
		for ( Bullet* bullet : allBullets ) {

			// Skip this iteration if the current bullet lifetime has elapsed
			if ( bullet->hasExpired() ) continue;

			// Update the bullet's position (i.e, move it across the window)
			bullet->updateBulletPosition();

			// Draw the bullet
			gameWindow.draw( *bullet );

		}

		// Has the player killed all enemies?
		if ( playerScore >= ( ( CONFIG_ENEMY_ROWS * CONFIG_ENEMY_COLUMNS ) * 10 ) ) {

			// Draw you win text
			texts[ 2 ].setString( "You Win!" );
			texts[ 2 ].setOrigin( sf::Vector2f( texts[ 2 ].getGlobalBounds().width / 2, texts[ 2 ].getGlobalBounds().height / 2 ) );
			texts[ 2 ].setPosition( sf::Vector2f( gameWindow.getSize().x / 2, gameWindow.getSize().y / 2 ) );
			gameWindow.draw( texts[ 2 ] );

		// There are still enemies remaining
		} else {

			// Loop through all of the enemies
			for ( int row = 0; row < CONFIG_ENEMY_ROWS; row++ ) {
				for ( int column = 0; column < CONFIG_ENEMY_COLUMNS; column++ ) {

					// Store the pointer to the enemy object for the current iteration
					Enemy *enemy = allEnemies[ row ][ column ];

					// Skip this iteration if this enemy is dead
					if ( enemy->isDead ) continue;

					// Run the method for when a bullet collides with the enemy, and pass address of score & bullets shot global variables
					enemy->doBulletHit( allBullets, &playerScore );

					// Move the enemy across the window
					enemy->moveAcrossWindow( CONFIG_ENEMY_SPEED, borders, playerScore );

					// If not obstructed by another enemy infront of this one and the shoot cooldown has elapsed, and the player isn't dead
					if ( !enemy->isObstructed( allEnemies ) && enemyShootCooldown.getElapsedTime().asMilliseconds() >= CONFIG_ENEMY_COOLDOWN && !player->isDead ) {

						// Continue only by configured chance
						if ( randomNumber( 0, CONFIG_ENEMY_CHANCE ) != 0 ) continue;

						// Shoot a bullet downwards to the player
						Bullet *bullet = enemy->shootBullet( 1, false );

						// Add the new bullet to the vector containing all active bullets
						allBullets.push_back( bullet );

						// Reset the enemy shoot cooldown clock
						enemyShootCooldown.restart();

					};

					// Draw the enemy
					gameWindow.draw( *enemy );

				}
			}

		}

		// Draw all the border shapes
		for ( int index = 0; index < 4; index++ ) gameWindow.draw( borders[ index ] );

		// Update and draw the score text
		texts[ 0 ].setString( "Score: " + std::to_string( playerScore ) );
		gameWindow.draw( texts[ 0 ] );

		// Update and draw the bullets shot text
		texts[ 1 ].setString( "Shots: " + std::to_string( playerBulletsShot ) );
		gameWindow.draw( texts[ 1 ] );

		// Render the base window
		gameWindow.display();

	}

	// Free the player object from heap memory
	delete player;

	// Delete all instansiated bullet objects
	for ( Bullet* bullet : allBullets ) delete bullet;

	// Loop through all enemy objects and free them from heap memory
	for ( int row = 0; row < CONFIG_ENEMY_ROWS; row++ ) {
		for ( int column = 0; column < CONFIG_ENEMY_COLUMNS; column++ ) {
			delete allEnemies[ row ][ column ];
		}
	}

	// Exit successfully once the program is finished
	return 0;

}
