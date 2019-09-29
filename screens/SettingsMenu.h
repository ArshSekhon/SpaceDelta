#pragma once
#include "..//Constants.h"
#include "..//Utility.h"
#include <allegro.h>

#define OPTION_COLOR makecol(11, 255, 255);
#define OPTION_COLOR_HOVERED makecol(255, 255, 255);

/**
 * @brief This class contains function related to diplaying the Settings Menu and handling the events for it.
 * 
 */
class SettingsMenu
{
private:
	BITMAP* bannerBitmap;
	GameState* gameState;
	BoundingBox soundSettingButton;
	BoundingBox gfxSettingButton;
	BoundingBox backButton;

	int backButtonColor = OPTION_COLOR;
	int gfxSettingsButtonColor = OPTION_COLOR;
	int soundSettingsButtonColor = OPTION_COLOR;

public:
	/**
	 * @brief Construct a new SettingsMenu object that would be used to display the Settings menu
	 * 
	 * @param gs Pointer to the game state struct that is shared by the entire game 
	 */
	SettingsMenu(GameState* gs);
	/**
	 * @brief Destroy the SettingsMenu struct and performs the required clean-up.
	 * 
	 */
	~SettingsMenu();
	
	/**
	 * @brief Draws Settings menu on to the buffer passed as an arguement 
	 * and also handles mouse click events for the same.
	 * 
	 * @param buffer Screen buffer or other buffer where the Settings screen has to be drawn.
	 * @param backgroundBitmap Pointer the bitmap to be used as the background 
	 * @param bannerBitmap Pointer the bitmap for the banner
	 * @param headingFont Pointer to the font used for text
	 */
	void drawSettingsMenuAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, BITMAP* bannerBitmap, FONT* headingFont);
};

