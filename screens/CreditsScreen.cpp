#include "CreditsScreen.h"

DIALOG creditsDialog = { d_textbox_proc, 0, 0,  0,  0,  0,  0, 0, 0, 0,   0, NULL, NULL, NULL };

DIALOG_PLAYER* creditsPlayer;
// constructor to do the initializations
CreditsScreen::CreditsScreen(GameState* gameState) {
	this->gameState = gameState;
	this->bannerBitmap = load_bitmap("assets/ui-elem/banner.bmp", NULL);
	// The text to be displayed on the screen
	this->credits = (char*)"The player sprite, background and some other UI elements of the game was created by the author of the game: Arsh Sekhon \n\nThe enemy sprites, laser sprites, mine sprite, some other sprites and UI elements of the game were derived from or inspired by https://opengameart.org/content/complete-spaceship-game-art-pack \n\n\nThe music for the game was obtained from: http://fredrikj.net/music/ and is unchanged. The music was publsihed under Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) license. \n\nSound FX were obtained from following sources:\nhttp://www.wavsource.com/sfx/sfx.htm \nhttps://opengameart.org/content/laser-fire \nhttps://opengameart.org/content/big-explosion";
}

void CreditsScreen::drawCreditsScreenAndHandleInput(BITMAP* buffer, BITMAP* backgroundBitmap, FONT* headingFont, FONT* textFont ) {
	//render background
	stretch_blit(backgroundBitmap, buffer, 0, 0, backgroundBitmap->w, backgroundBitmap->h, 0, 0, SCREEN_W, SCREEN_H);

	

	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.5, "CREDITS", COLOR_TEXT, -1);
		creditsPlayer=Utility::draw_wrapping_text(buffer, textFont, &creditsDialog, this->credits, SCREEN_W*0.2, SCREEN_H * 0.32, SCREEN_W*0.6, SCREEN_H*0.4, 10);
		backButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.78, 0.4, "BACK", backButtonColor, -1);
	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.75, "CREDITS", COLOR_TEXT, -1);
		creditsPlayer=Utility::draw_wrapping_text(buffer, textFont, &creditsDialog, this->credits, SCREEN_W * 0.2, SCREEN_H * 0.3, SCREEN_W * 0.6, SCREEN_H * 0.4, 10);
		backButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.78, 0.6, "BACK", backButtonColor, -1);
	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.23, 1, "CREDITS", COLOR_TEXT, -1);
		creditsPlayer=Utility::draw_wrapping_text(buffer, textFont, &creditsDialog, this->credits, SCREEN_W * 0.25, SCREEN_H * 0.3, SCREEN_W * 0.5, SCREEN_H * 0.4, 10);
		backButton = Utility::textout_centre_scaled(buffer, headingFont, SCREEN_W / 2, SCREEN_H * 0.75, .8, "BACK", backButtonColor, -1);
	}

	// handle mouse clicks for the backbutton
	if (Utility::mouseInTheBoundingBox(backButton)) {
		gameState->mouseHover = 1;
		this->backButtonColor = OPTION_COLOR_HOVERED;
		//if mouse is clicked on the back button
		if ((gameState->pendingMouseClick==1) && !(mouse_b & 1)) {
			gameState->gameScreen = GAME_SCREEN_MAIN_MENU;
			gameState->mouseHover = 0;
			if (creditsPlayer) {

				shutdown_dialog(creditsPlayer);
				creditsPlayer = NULL;
			}
			gameState->pendingMouseClick = 0;
			rest(300);
			return;
		}
	}
	else {
		this->backButtonColor = OPTION_COLOR;
		gameState->mouseHover = 0;
	}
	 

}