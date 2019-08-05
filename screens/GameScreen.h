#pragma once
#include "../constants.h"
#include "../Utility.h"
#include <allegro.h>

class GameScreen
{
private:
	GameState* gameState;
	BITMAP* gameBackground;

public:
	GameScreen(GameState* gameState);
	~GameScreen();
	void drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont);
};

