#pragma once
#define CONFIG_FILENAME "SpaceDelta.cfg"

#define NUMBER_OF_QUESTIONS_PER_GAME 10

// GFX RESOLUTIONS
#define GFX_RES_640_X_480 0
#define GFX_RES_960_X_720 1
#define GFX_RES_1280_X_960 2

// GFX screen mode
#define GFX_MODE_WINDOWED 0
#define GFX_MODE_FULLSCREEN 1

// Game states
#define GAME_SCREEN_LOADING 1
#define GAME_SCREEN_MAIN_MENU 2
#define GAME_SCREEN_SETTINGS 3
#define GAME_SCREEN_GFX_SETTINGS 4
#define GAME_SCREEN_SOUND_SETTINGS 5 
#define GAME_SCREEN_START 6
#define GAME_SCREEN_HELP 7
#define GAME_SCREEN_PLAY 8
#define GAME_SCREEN_RESULTS 9
#define GAME_SCREEN_CREDITS 10

//SOUND EFFECTS
#define SOUND_CLICK 0
#define SOUND_CHEERING 1
#define SOUND_BUZZER 2
#define SOUND_BOING 3

// Error and Exception codes
#define EXCEPTION_READING_QUESTION_FILE 101
#define EXCEPTION_READING_ANSWER_FILE 102
#define EXCEPTION_NOT_ENOUGH_QUESTIONS 103

#define ERROR_ALLEGRO_INIT 103
#define ERROR_ALLEGRO_SOUND_INIT 104
#define ERROR_ALLEGRO_KEYBOARD_INIT 105
#define ERROR_ALLEGRO_GFX_CHANGE 106

// colors
#define COLOR_BG makecol(18,39,34)
#define COLOR_TEXT makecol(11,255,255)
#define COLOR_HUD_TEXT makecol(96,57,28)

/**
 * @brief Struct used to store the state of the game.
 *
 */
struct GameState {

	int resolution_x;
	int resolution_y;
	// full screen 
	int fullscreen;

	// sound settings
	int sound_volume;
	int music_volume;

	int gameScreen;

	int mouseHover;
	int exitGame;

	int gfxSettingsUpdated;
	int soundSettingsUpdated;

	int skip_intro;
	 

	int health;
	int currentScore;

	int bgMusicPlaying;
	int pendingMouseClick;
};

/**
 * @brief Struct used to store the Bounds of a control element like button.
 *
 */
struct BoundingBox {
	int x;
	int y;
	int w;
	int h;
};
