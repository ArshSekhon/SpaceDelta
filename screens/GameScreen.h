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
#include <allegro.h>

class GameScreen
{
private:
	GameState* gameState;
	BITMAP* gameBackground;
	BITMAP* genericBackground;
	BITMAP* bannerBitmap;
	void displayHealthBarAndScore(BITMAP* buffer, FONT* headingFont);
	PlayerShip* playerShip;


	std::vector<Bullet*> bullets ;
	std::vector<Explosion*> explosions;
	std::vector<MineBomb*> mineBombs; 
	std::vector<EnemyShip*> enemyShips;

	void checkHits(BITMAP* buffer);
	int numFrames; 
	int bulletDamage = 10;
	int mineBombDamage = 30;
	void displayResultsBannerAndHandleInput(BITMAP* buffer, FONT* textFont);
	unsigned long timeElasped = 0, startTime = 0;
	
	unsigned long lastmineReleaseTime = 0;
	int mineReleaseDelay = 0;

	unsigned long lastEnemyReleaseTime = 0;
	int enemyReleaseDelay = 0;
	void triggerReleases();

public:
	GameScreen(GameState* gameState);
	~GameScreen();
	void drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont);
};

