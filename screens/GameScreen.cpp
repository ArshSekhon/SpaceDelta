#include "GameScreen.h"



GameScreen::GameScreen(GameState* gameState)
{
	this->gameState = gameState;
	this->gameBackground = load_bitmap("assets/backgrounds/game-bg.bmp", NULL);


}


GameScreen::~GameScreen()
{
}


void GameScreen::drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont) {
	stretch_blit(gameBackground, buffer, 0, 0, gameBackground->w, gameBackground->h, 0, 0, SCREEN_W, SCREEN_H);

}