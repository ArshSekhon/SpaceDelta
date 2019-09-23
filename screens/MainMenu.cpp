#include "MainMenu.h"
#include "../Constants.h"  
#include <allegro.h>
#include "../Utility.h"



MainMenu::MainMenu(GameState* gs) { 
	this->gameState = gs;
	this->background = load_bitmap(MAIN_MENU_BUTTON_SPRITE, NULL);
	//this->gameTitle = load_bitmap("assets/main-menu/GameTitleBanner.bmp", NULL);
	//this->bannerBitmap = load_bitmap("assets/ui-elem/Banner_Sq.bmp", NULL);
	this->buttonsBitmap = load_bitmap("assets/ui-elem/mainmenu-buttons.bmp", NULL);
	 
}

int MainMenu::showMainMenu(BITMAP* buffer) { 
	stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);
	//draw buffer to screen and clear buffer
	 
	//draw buttons
	if (SCREEN_W == 640 && SCREEN_H == 480) {

		int margin = 13;
		float width_relative_to_screen = 0.13;
		int y_first_button = SCREEN_H * 0.35;
		int x_first_button = SCREEN_W * 0.77;
		playButton = draw_play_button(buffer, buttonsBitmap, x_first_button, y_first_button, width_relative_to_screen, cursorOverPlayButton);
		settingsButton = draw_options_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H)/MAIN_MENU_BUTTON_W*SCREEN_W* width_relative_to_screen) * 1, width_relative_to_screen, cursorOverOptionsButton);
		creditsButton = draw_credits_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) * 2, width_relative_to_screen, cursorOverCreditsButton);
		exitButton = draw_exit_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) * 3, width_relative_to_screen, cursorOverExitButton);
	
	}
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		int margin = 15;
		float width_relative_to_screen = 0.13;
		int y_first_button = SCREEN_H * 0.35;
		int x_first_button = SCREEN_W * 0.77;
		playButton = draw_play_button(buffer, buttonsBitmap, x_first_button, y_first_button, width_relative_to_screen, cursorOverPlayButton);
		settingsButton = draw_options_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen)*1, width_relative_to_screen, cursorOverOptionsButton);
		creditsButton = draw_credits_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) *2, width_relative_to_screen, cursorOverCreditsButton);
		exitButton = draw_exit_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) * 3, width_relative_to_screen, cursorOverExitButton);

	}
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		int margin = 25;
		float width_relative_to_screen = 0.13;
		int y_first_button = SCREEN_H * 0.35;
		int x_first_button = SCREEN_W * 0.77;
		playButton = draw_play_button(buffer, buttonsBitmap, x_first_button, y_first_button, width_relative_to_screen, cursorOverPlayButton);
		settingsButton = draw_options_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) * 1, width_relative_to_screen, cursorOverOptionsButton);
		creditsButton = draw_credits_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) * 2, width_relative_to_screen, cursorOverCreditsButton);
		exitButton = draw_exit_button(buffer, buttonsBitmap, x_first_button, y_first_button + (margin + ((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen) * 3, width_relative_to_screen, cursorOverExitButton);

	}
	 
	// handle clicks on the start button
	if (Utility::mouseInTheBoundingBox(playButton)) {
		gameState->mouseHover = 1;

		this->cursorOverPlayButton = 1;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 0;

		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)){

			if (!gameState->skip_intro)
				gameState->gameScreen = GAME_SCREEN_START;
			else
				gameState->gameScreen = GAME_SCREEN_PLAY;

			//reset the score and current question number 
			gameState->currentScore = 0;
			gameState->health = 100;

			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the settings button
	else if (Utility::mouseInTheBoundingBox(settingsButton)) {
		gameState->mouseHover = 1;

		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 1;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 0;

		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)){
			gameState->gameScreen = GAME_SCREEN_SETTINGS;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the credits button
	else if (Utility::mouseInTheBoundingBox(creditsButton)) {
		gameState->mouseHover = 1;

		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 1;
		this->cursorOverExitButton = 0;

		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)){
			gameState->gameScreen = GAME_SCREEN_CREDITS;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300);
		}
	}
	// handle clicks on the credits button
	else if (Utility::mouseInTheBoundingBox(exitButton)) {
		gameState->mouseHover = 1;


		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 1;


		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
			gameState->exitGame = 1;
			gameState->pendingMouseClick = 0;
		}
	}
	else {
		gameState->mouseHover = 0;
		this->cursorOverPlayButton = 0;
		this->cursorOverOptionsButton = 0;
		this->cursorOverCreditsButton = 0;
		this->cursorOverExitButton = 0;
	}


	//mouse coordinates
	//textprintf(buffer, font, 10, 10, -1, "X:%d Y:%d S:%d S:%d C:%d E:%d GS:%d FS:%d", mouse_x, mouse_y, startButton.y, settingsButton.y, creditsButton.y, exitButton.y, gameState->gameScreen, gameState->fullscreen);
	

	return this->gameState->gameScreen;
}
BoundingBox MainMenu::draw_play_button(BITMAP* buffer, 
										BITMAP* sprite, 
										int d_x, 
										int d_y, 
										float width_relative_to_screen,
										bool hovered) {
	BoundingBox boundingBox = {
		d_x,
		d_y,
		SCREEN_W * width_relative_to_screen,
		((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen
	};

	if(!hovered)
		masked_stretch_blit(sprite,
			buffer, 0, 0, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);
	else
		masked_stretch_blit(sprite,
			buffer, 149, 0, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);

	
	return boundingBox;
}

BoundingBox MainMenu::draw_options_button(BITMAP* buffer,
											BITMAP* sprite, 
											int d_x,
											int d_y,
											float width_relative_to_screen,
											bool hovered) {

	BoundingBox boundingBox = {
		d_x,
		d_y,
		SCREEN_W * width_relative_to_screen,
		((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen
	};

	if (!hovered)
		masked_stretch_blit(sprite,
			buffer, 0, 93, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H+1,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);
	else
		masked_stretch_blit(sprite,
			buffer, 149, 93, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);


	return boundingBox;

}

BoundingBox MainMenu::draw_credits_button(BITMAP* buffer,
											BITMAP* sprite, 
											int d_x,
											int d_y,
											float width_relative_to_screen,
											bool hovered) {

	BoundingBox boundingBox = {
		d_x,
		d_y,
		SCREEN_W * width_relative_to_screen,
		((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen
	};

	if (!hovered)
		masked_stretch_blit(sprite,
			buffer, 0, 187, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H ,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);
	else
		masked_stretch_blit(sprite,
			buffer, 149, 186, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H + 1,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);


	return boundingBox;

}

BoundingBox MainMenu::draw_exit_button(BITMAP* buffer,
										BITMAP* sprite, 
										int d_x,
										int d_y,
										float width_relative_to_screen,
										bool hovered) {

	BoundingBox boundingBox = {
		d_x,
		d_y,
		SCREEN_W * width_relative_to_screen,
		((float)MAIN_MENU_BUTTON_H) / MAIN_MENU_BUTTON_W * SCREEN_W * width_relative_to_screen
	};

	if (!hovered)
		masked_stretch_blit(sprite,
			buffer, 0, 280, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);
	else
		masked_stretch_blit(sprite,
			buffer, 149, 280, MAIN_MENU_BUTTON_W, MAIN_MENU_BUTTON_H,
			boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);


	return boundingBox;

}