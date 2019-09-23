#pragma once
#include "..//Constants.h"
#include "..//ConfigManager.h"
#include "..//Utility.h"
#include <allegro.h>

#define OPTION_COLOR makecol(11, 255, 255);
#define OPTION_COLOR_HOVERED makecol(255, 255, 255);

/**
 * @brief This class contains function related to diplaying the Sound related Settings screen, handling the events for the screen and
 * managing and appling the Sound related settings. 
 * 
 */
class SoundSettingsMenu
{
public:
	/**
	 * @brief Construct a new SoundSettingsMenu object that would be used to create Sound related menu
	 * 
	 * @param gs Pointer to the game state struct that is shared by the entire game
	 * @param configManager Pointer to the ConfigManager object that would be used by Sound related Menu to load and save the configurations
	 */
	SoundSettingsMenu(GameState* gs, ConfigManager* configManager);
	/**
	 * @brief Destroy the SoundSettingsMenu object and performs the required clean-up.
	 * 
	 */
	~SoundSettingsMenu();
	/**
	 * @brief Draws Sound related settings menu on to the buffer passed as an arguement 
	 * and also handles mouse clicks for the Sound related settings menu. It also works with ConfigManager to load and save Sound related related setting
	 * and apply them to the game when apply button is pressed.
	 * 
	 * @param buffer Screen buffer or other buffer where the Sound related settings screen has to be drawn.
	 */
	void drawSoundSettingsMenuAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, FONT* font);
private:
	GameState* gameState;
	ConfigManager* configManager;
	BITMAP* bannerBitmap;
	BoundingBox backButton;
	BoundingBox applyButton; 
	int soundVolume;
	int musicVolume;
	const char** levels;
	BoundingBox* soundVolChangeArrows;
	BoundingBox* musicVolChangeArrows;
	void changeSoundSettings(int musicVol, int soundVol, GameState* gameState);

	int backButtonColor = OPTION_COLOR;
	int applyButtonColor = OPTION_COLOR;

	int soundVolChangeArrowsColor = OPTION_COLOR;
	int musicVolChangeArrowsColor = OPTION_COLOR;
};

