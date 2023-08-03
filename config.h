// Ensure duplications are avoided
#pragma once

// Include native libraries
#include <string>

/*******************************************************************************
This is the configuration file, where core features of the game can be adjusted.
/******************************************************************************/

// If the console should be hidden when the application is launched
const bool CONFIG_CONSOLE_HIDE = true;

// The relative path of the background texture file used for the window
const std::string CONFIG_WINDOW_BACKGROUND = "Textures/Stars.png";

// The relative path of the font file used for text
const std::string CONFIG_WINDOW_FONT = "Fonts/Pilot Command.ttf";

// The amount of padding around the inside of the gamewindow (i.e., the border).
const unsigned int CONFIG_WINDOW_PADDING = 25;

// The title of the game window displayed on the toolbar strip
const std::string CONFIG_WINDOW_TITLE = "Space Invaders";

// The maximum framerate for the game to prevent unusual behaviour.
const unsigned int CONFIG_FRAMERATE_MAX = 60;

// If the framerate should be locked at the screen's refresh rate (vertical sync). 
const bool CONFIG_FRAMERATE_LOCK = true;

// The cooldown for the player shooting their bullets, in milliseconds.
const unsigned int CONFIG_PLAYER_COOLDOWN = 500;

// The speed at which the player moves across the screen
const unsigned int CONFIG_PLAYER_SPEED = 5;

// The size of the player shapes
const unsigned int CONFIG_PLAYER_RADIUS = 20;

// The speed at which a bullet travels for both players and enemies
const unsigned int CONFIG_BULLET_SPEED = 5;

// The lifetime of the bullet, in milliseconds.
const unsigned int CONFIG_BULLET_LIFETIME = 2000;

// The size of the bullet shapes
const unsigned int CONFIG_BULLET_WIDTH = 5;
const unsigned int CONFIG_BULLET_HEIGHT = 10;

// The amount of enemies that are created, defined by rows x columns.
const unsigned int CONFIG_ENEMY_ROWS = 3;
const unsigned int CONFIG_ENEMY_COLUMNS = 9;

// The size of the enemy shapes
const unsigned int CONFIG_ENEMY_RADIUS = 20;

// The speed at which the enemies move across the screen
const float CONFIG_ENEMY_SPEED = 0.5;

// The interval that enemies should move down, in milliseconds.
const unsigned int CONFIG_ENEMY_TIME = 10000;

// The cooldown for the enemy shooting their bullets, in milliseconds.
const unsigned int CONFIG_ENEMY_COOLDOWN = 2000;

// The chance of an enemy shooting a bullet.
const unsigned int CONFIG_ENEMY_CHANCE = 10;