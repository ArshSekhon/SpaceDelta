#pragma once
#include "../constants.h"
#include  "../ConfigManager.h"

#include "../Utility.h"
#include <allegro.h>

#define OPTION_COLOR makecol(11, 255, 255);
#define OPTION_COLOR_HOVERED makecol(255, 255, 255);
/**
 * @brief This class contains function related to diplaying the Game Intro screen, handling the events for the screen and
 * managing and appling the Game Intro. 
 * 
 */
class GameHelpScreen
{
private:
	BITMAP* bannerBitmap;
	GameState* gameState;
	BITMAP* tempScreenBmp;
	char* introText;
	FONT* bigFont;
	BoundingBox skipIntroButton;
	BoundingBox closeButton;
	ConfigManager* configManager;


	int closeButtonColor = OPTION_COLOR;
	int neverShowAgainButtonColor = OPTION_COLOR;
public:
	/**
	 * 
	 * @brief Construct a new GameIntroScreen object that would be used to show an intro screen when game start.
	 * 
	 * @param gameState Pointer to the game state struct that is shared by the entire game
	 * @param configManager Pointer to the ConfigManager object that would be used to load and save the config related to game intro screen
	 * 
	 */
	GameHelpScreen(GameState* gameState);


	/**
	 * @brief Draws game intro screen on to the buffer passed as an arguement 
	 * and also handles mouse click events for the same.
	 * 
	 * @param buffer Screen buffer or other buffer where the game intro screen screen has to be drawn.
	 */
	void drawHelpScreenAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, FONT* headingFont, FONT* textFont, char* buttonText);
};

