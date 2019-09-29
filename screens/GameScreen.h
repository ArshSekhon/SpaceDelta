#pragma once
#include "../constants.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../entities/MineBomb.h"
#include "../entities/EnemyShip.h"
#include "../entities/PlayerShip.h"
#include "../entities/Bullet.h"
#include "../entities/Explosion.h"
#include "../Utility.h"
#include "../Sprite.h"
#include "../SoundManager.h"
#include "../assets/bmp_defines.h"
#include <allegro.h>

#define OPTION_COLOR makecol(11, 255, 255);
#define OPTION_COLOR_HOVERED makecol(255, 255, 255);

class GameScreen
{
private:
	GameState* gameState;
	// pointers to the bitmaps for the UI
	BITMAP* gameBackground;
	BITMAP* genericBackground;
	BITMAP* bannerBitmap;
	// function to render score and health information
	void displayHealthBarAndScore(BITMAP* buffer, FONT* headingFont);
	// Pointer to the player ship object
	PlayerShip* playerShip;

	// Pointers to store various game objects like bullets, enemies, minebombs and explosions
	std::vector<Bullet*> bullets ;
	std::vector<Explosion*> explosions;
	std::vector<MineBomb*> mineBombs; 
	std::vector<EnemyShip*> enemyShips;

	// function to check for collisions
	void checkHits(BITMAP* buffer);
	
	int bulletDamage = 10;
	int mineBombDamage = 30;
	// function to display the result banner at the end of the game
	void displayResultsBannerAndHandleInput(BITMAP* buffer, FONT* textFont);
	// vars for ensure proper timing and fps
	int numFrames; 
	unsigned long timeElasped = 0, startTime = 0;
	// vars to store information regarding the timming of mine bomb and enemy releases
	unsigned long lastmineReleaseTime = 0;
	int mineReleaseDelay = 0;
	unsigned long lastEnemyReleaseTime = 0;
	int enemyReleaseDelay = 0;
	// function to check if it is the time for any new releases of enemy entities 
	void triggerReleases();

	long gameOverTime = -1;
	int gameOverDelay = 1000;

	// bounding boxes for the buttons on the results banner
	BoundingBox restartGameButton;
	BoundingBox exitToMainMenuButton;
	
	int exitToMainMenuButtonColor, restartGameButtonColor;
	SoundManager* soundManager;

	DATAFILE* bitmaps_datafile;

public:
	/**
	 * @brief Construct a new Game Screen object
	 * 
	 * @param gameState Pointer to the game state struct
	 * @param soundManager Pointer to the sound manager object
	 * @param bitmap_datafile Pointer to the datafile containing bitmaps
	 */
	GameScreen(GameState* gameState, SoundManager* soundManager, DATAFILE* bitmap_datafile);
	/**
	 * @brief Destroy the Game Screen object
	 * 
	 */
	~GameScreen();
	/**
	 * @brief Draws the game screen to the bitmap and handles the keyboard input
	 * 
	 * @param buffer Bitmap where the game screen is rendered
	 * @param headingFont Font used for the headings
	 * @param textFont Font used for the texts
	 */
	void drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont);
};

