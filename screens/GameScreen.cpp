#include "GameScreen.h" 


GameScreen::GameScreen(GameState* gameState, SoundManager* soundManager)
{
	// initializations
	this->gameState = gameState;
	this->soundManager = soundManager; 
	// load bitmaps
	this->gameBackground = load_bitmap("assets/backgrounds/game-bg.bmp", NULL);
	this->genericBackground = load_bitmap("assets/backgrounds/background-menus.bmp", NULL);
	this->bannerBitmap = load_bitmap("assets/ui-elem/banner.bmp", NULL);
	// create new playerships and minebombs
	this->playerShip = new PlayerShip(&this->bullets, 100, this->soundManager); 
	this->mineBombs.push_back(new MineBomb(200,100,1)); 
	this->mineBombs.push_back(new MineBomb((std::rand() % ((int)(PLAY_REGION_W - 10 * SCALING_FACTOR_RELATIVE_TO_1280))), -55 * SCALING_FACTOR_RELATIVE_TO_1280, 1));

	  
	srand(time(NULL)); 
	this->mineReleaseDelay = std::rand() % (5000);

}

GameScreen::~GameScreen()
{	
	// do the cleanup
	this->playerShip->~PlayerShip();
	for (int i = 0; i < this->bullets.size(); i++)
		this->bullets[i]->~Bullet();
	for (int i = 0; i < this->mineBombs.size(); i++)
		this->mineBombs[i]->~MineBomb();
	for (int i = 0; i < this->enemyShips.size(); i++)
		this->enemyShips[i]->~EnemyShip();
	for (int i = 0; i < this->explosions.size(); i++)
		this->explosions[i]->~Explosion();
}
  
void GameScreen::displayHealthBarAndScore(BITMAP* buffer, FONT* customFont) {

	// calculate the position and dimensions
	int labelsX = PLAY_REGION_W + SCREEN_W / 30;
	int healthLabelY = 386 * SCALING_FACTOR_RELATIVE_TO_1280;
	int healthBarY = healthLabelY + 50 * SCALING_FACTOR_RELATIVE_TO_1280;
	int healthBarWidth = SCREEN_W / 5;
	int healthBarHeight = 25 * SCALING_FACTOR_RELATIVE_TO_1280;

	// display label text
	Utility::textout_magnified(buffer, customFont, labelsX, healthLabelY, 0.5*SCALING_FACTOR_RELATIVE_TO_1280, "HEALTH", makecol(11, 255, 255), -1);
	// create empty health bar
	rectfill(buffer, labelsX , healthBarY, labelsX + healthBarWidth, healthBarY + healthBarHeight, makecol(0, 0, 0));
	// if health !==0 fill the health bar up as required
	if(this->gameState->health != 0)
		rectfill(buffer, labelsX, healthBarY, labelsX + (healthBarWidth*((1.0*this->gameState->health)/100)), healthBarY + healthBarHeight, makecol(0, 255, 0)); 
	// display score related information
	Utility::textout_magnified(buffer, customFont, labelsX, 486 * SCALING_FACTOR_RELATIVE_TO_1280, 0.5 * SCALING_FACTOR_RELATIVE_TO_1280, "YOUR SCORE", makecol(11, 255, 255), -1);
	Utility::textout_magnified(buffer, font, labelsX, 530 * SCALING_FACTOR_RELATIVE_TO_1280, 2 * SCALING_FACTOR_RELATIVE_TO_1280, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


}

void GameScreen::displayResultsBannerAndHandleInput(BITMAP* buffer, FONT* textFont)
{

 	stretch_blit(genericBackground, buffer, 0, 0, genericBackground->w, genericBackground->h, 0, 0, SCREEN_W, SCREEN_H);

	// draw graphics on screen for 640x480 mode
	if (SCREEN_W == 640 && SCREEN_H == 480) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.5, "RESULTS", COLOR_TEXT, -1);


		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.55, "SCORE", makecol(255, 255, 255), -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, .7, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .4, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .4, "RESTART GAME", restartGameButtonColor, -1);


	}
	// draw graphics on screen for 960x720 mode
	else if (SCREEN_W == 960 && SCREEN_H == 720) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, SCREEN_W * 0.1, SCREEN_H * 0.1, SCREEN_W * 0.8, SCREEN_H * 0.8);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 0.75, "RESULTS", COLOR_TEXT, -1);


		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.65, "SCORE", makecol(255, 255, 255), -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, .9, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .4, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .4, "RESTART GAME", restartGameButtonColor, -1);

	

	}
	// draw graphics on screen for 1280x960 mode
	else  if (SCREEN_W == 1280 && SCREEN_H == 960) {
		masked_stretch_blit(bannerBitmap, buffer, 0, 0, bannerBitmap->w, bannerBitmap->h, (SCREEN_W - bannerBitmap->w) / 2, (SCREEN_H - bannerBitmap->h) / 2, bannerBitmap->w, bannerBitmap->h);

		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.23, 1, "RESULTS", COLOR_TEXT, -1);
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.43, 0.75, "SCORE", makecol(255,255,255), -1); 
		 
		Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 2, SCREEN_H * 0.5, 1, std::to_string(this->gameState->currentScore).c_str(), makecol(255, 255, 255), -1);
		 


		exitToMainMenuButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W / 3, SCREEN_H * 0.75, .5, "EXIT TO MAIN MENU", exitToMainMenuButtonColor, -1);
		restartGameButton = Utility::textout_centre_scaled(buffer, textFont, SCREEN_W * 2.0 / 3, SCREEN_H * 0.75, .5, "RESTART GAME", restartGameButtonColor, -1);


	} 
	exitToMainMenuButtonColor = restartGameButtonColor = OPTION_COLOR;


	gameState->mouseHover = 0;

	// handle clicks on the apply Button
	if (Utility::mouseInTheBoundingBox(exitToMainMenuButton)) {
		gameState->mouseHover = 1;
		exitToMainMenuButtonColor = OPTION_COLOR_HOVERED;

		if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
			// exit to Main Menu 

			gameState->needPlayerReset = 1;

			gameState->gameScreen = GAME_SCREEN_MAIN_MENU;
			gameState->mouseHover = 0;
			gameState->pendingMouseClick = 0;
			rest(300); 
		}
	}
	// handle clicks on the back button
	else if (Utility::mouseInTheBoundingBox(restartGameButton)) {
		gameState->mouseHover = 1;
		restartGameButtonColor = OPTION_COLOR_HOVERED

			if ((gameState->pendingMouseClick == 1) && !(mouse_b & 1)) {
				gameState->needPlayerReset = 1;

				gameState->pendingMouseClick = 0;

				rest(300); 
			}
	}



	// restart game if KEY R is pressed
	if (key[KEY_R]) {
		gameState->needPlayerReset = 1;
	}

	
}

void GameScreen::drawGameScreenAndHandleInput(BITMAP* buffer, FONT* headingFont, FONT* textFont) {
	if (this->startTime == 0) {
		startTime = clock();
	}
	else {
		timeElasped = clock() - startTime;
	}
	// if game needs a reset, reset all vars and game state to initial value
	if (gameState->needPlayerReset == 1) {
		gameState->needPlayerReset = 0;
		this->playerShip->~PlayerShip();

		this->enemyShips.clear();
		this->mineBombs.clear();
		this->bullets.clear();

		this->playerShip = new PlayerShip(&this->bullets, 100, this->soundManager);
		this->gameState->health = 100;
		this->gameState->currentScore = 0;
		this->gameOverTime = -1;
	}
	// if game is over then display the results banner
	if (this->gameState->health <= 0 && clock() - gameOverTime > gameOverDelay)
	{

		this->displayResultsBannerAndHandleInput(buffer, headingFont);
		return;
	}
	// if game is not over yet
	else{

		// check if it is the time to do new release of any of the enemy entities
		triggerReleases();
		// render the background
		stretch_blit(gameBackground, buffer, 0, 0, gameBackground->w, gameBackground->h, 0, 0, SCREEN_W, SCREEN_H);

		// display health bar
		this->displayHealthBarAndScore(buffer, headingFont);
		// check for collisions
		this->checkHits(buffer);

		// render the enemy ships
		for (int i = 0; i < this->enemyShips.size(); i++) {

			this->enemyShips[i]->render(buffer);
		}
		// render bullets
		for (int i = 0; i < this->bullets.size(); i++) {
			this->bullets[i]->renderBullet(buffer);
			if (this->bullets[i]->isOffScreen() || this->bullets[i]->hasExploded())
			{
				this->bullets[i]->~Bullet();
				this->bullets.erase(this->bullets.begin() + i);
			}
		} 
		// render player ship and handle controls for it
		this->playerShip->showShipAndHandleControls(buffer);
		// render the explosions
		for (int i = 0; i < this->explosions.size(); i++) {

			if (this->explosions[i]->hasEnded()) {
				this->explosions[i]->~Explosion();
				this->explosions.erase(this->explosions.begin() + i);
			}
			else {
				this->explosions[i]->renderExplosion(buffer);
			}
		} 
		// render the minebombs
		for (int i = 0; i < this->mineBombs.size(); i++) {

			if (this->mineBombs[i]->hasExploded()) {
				this->mineBombs[i]->~MineBomb();
				this->mineBombs.erase(this->mineBombs.begin() + i);
			}
			else {
				this->mineBombs[i]->render(buffer);
			}
		}
		  

		//textprintf_ex(buffer, font, PLAY_REGION_W + SCREEN_W / 25, 10, makecol(255, 255, 255), -1, "Bullets: %d Explosions: %d Enemies: %d Mines: %d", this->bullets.size(), this->explosions.size(), this->enemyShips.size(), this->mineBombs.size());

	}
	
	 // if player health is 0 render an explosion and end the game
	if (this->gameState->health <= 0 && gameOverTime==-1) {

		//add explosion
		this->explosions.push_back(new Explosion(BIG_EXPLOSION, playerShip->getSprite()->getCenterX(), playerShip->getSprite()->getCenterY(), 20));

		this->soundManager->playSound(SOUND_EXPLOSION, 1000);

		playerShip->kill();

		gameOverTime = clock();
	}

	 
	// if player presses Ctrl+H render the help menu
	if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_H]) {
		gameState->gameScreen = GAME_SCREEN_HELP;
	} 
	 
}

void GameScreen::checkHits(BITMAP* buffer)
{
	Sprite* mainSprite;
	Sprite* otherSprite;

	// check bullet hits
	for (int i = 0; i < this->bullets.size(); i++)
	{
		mainSprite = this->bullets[i]->getSprite();

		//check bullets by enemies
		if (this->bullets[i]->isEnemyBullet)
		{
			//check if hit player
			otherSprite = this->playerShip->getSprite();

			if (this->playerShip->isAlive() && mainSprite->collided(buffer, mainSprite->getW()/6, mainSprite->getH()/5, otherSprite, otherSprite->getW()/100, otherSprite->getH()/4)) {
				// update health for player
				if (this->gameState->health - this->bullets[i]->getDamageVal() > 0)
					this->gameState->health -= this->bullets[i]->getDamageVal();
				else
					this->gameState->health = 0;

				//add explosion
				this->explosions.push_back(new Explosion(SMALL_EXPLOSION, mainSprite->getCenterX(), mainSprite->getY() + mainSprite->getH(), 5));

				// play sound effect
				this->soundManager->playSound(SOUND_EXPLOSION, 2000);




				//remove bullet
				this->bullets[i]->~Bullet();
				this->bullets.erase(this->bullets.begin() + i);
				i--;

			}
		} 
		else
		{
			//check all mine bombs
			for (int j = 0; j < this->mineBombs.size() && i < this->bullets.size(); j++)
			{
				otherSprite = this->mineBombs[j]->getSprite();
				if (mainSprite->collided(buffer, mainSprite->getW() / 6, mainSprite->getH() / 5, otherSprite, otherSprite->getW() / 6, otherSprite->getH() / 6)) { 

					//add explosion
					this->explosions.push_back(new Explosion(MEDIUM_EXPLOSION, otherSprite->getCenterX(), otherSprite->getCenterY(), 5));
					this->soundManager->playSound(SOUND_EXPLOSION, 1500);

					//remove minebomb
					this->mineBombs[j]->~MineBomb();
					this->mineBombs.erase(this->mineBombs.begin() + j);  
					j--;

					//remove bullet
					this->bullets[i]->~Bullet();
					this->bullets.erase(this->bullets.begin() + i);
					i--;

					this->gameState->currentScore += 75;
				}

			}

			//check all bullets
			for (int j = 0; j < this->bullets.size() && i < this->bullets.size(); j++)
			{
				if (this->bullets[j]->isEnemyBullet) {
					otherSprite = this->bullets[j]->getSprite();
					if (mainSprite->collided(buffer, mainSprite->getW() / 6, mainSprite->getH() / 5, otherSprite, otherSprite->getW() / 6, otherSprite->getH() / 6)) { 
						//add explosion
						this->explosions.push_back(new Explosion(SMALL_EXPLOSION, otherSprite->getCenterX(), otherSprite->getCenterY(), 5));


						//remove bullet
						this->bullets[j]->~Bullet();
						this->bullets.erase(this->bullets.begin() + j);

						if (j < i)
							i--;

						//remove bullet
						this->bullets[i]->~Bullet();
						this->bullets.erase(this->bullets.begin() + i);

						this->gameState->currentScore += 2;
					}
				}
			} 

			//check all enemies for hit
			for (int j = 0; j < this->enemyShips.size() && i < this->bullets.size(); j++) {
				otherSprite = this->enemyShips[j]->getSprite();
				if (mainSprite->collided(buffer, mainSprite->getW() / 6, mainSprite->getH() / 5, otherSprite, otherSprite->getW() / 5, otherSprite->getH() / 5)) {
					//collision has happened
					if (this->enemyShips[j]->makeBulletImpact(this->bullets[i]->getDamageVal()) == 0) 
					{ 
						//add explosion
						this->explosions.push_back(new Explosion(BIG_EXPLOSION, otherSprite->getCenterX(), otherSprite->getCenterY(), 5));

						this->soundManager->playSound(SOUND_EXPLOSION, 1000);

						if (this->enemyShips[j]->getShipType() == ENEMY_SHIP_SMALL)
							this->gameState->currentScore += 50;
						else
							this->gameState->currentScore += 100;

						this->enemyShips[j]->~EnemyShip();
						this->enemyShips.erase(this->enemyShips.begin() + j);
						j--;
					}
					else {

						//add explosion
						this->explosions.push_back(new Explosion(SMALL_EXPLOSION, mainSprite->getCenterX(), mainSprite->getY(), 5));

						this->gameState->currentScore += 5;
					}


					//remove bullet
					this->bullets[i]->~Bullet();
					this->bullets.erase(this->bullets.begin() + i);

					i--;

				}

			} 
		}
	}
	//check for hits by minebombs
	for (int i = 0; i < this->mineBombs.size(); i++) {


		mainSprite = this->mineBombs[i]->getSprite();

		//check if hit player
		otherSprite = this->playerShip->getSprite();

		if (this->playerShip->isAlive() && mainSprite->collided(buffer, mainSprite->getW() / 6, mainSprite->getH() / 5, otherSprite, otherSprite->getW() / 100, otherSprite->getH() / 4)) {

			if (this->gameState->health - this->mineBombs[i]->getDamageVal() > 0)
				this->gameState->health -= this->mineBombs[i]->getDamageVal();
			else
				this->gameState->health = 0;

			//add explosion
			this->explosions.push_back(new Explosion(MEDIUM_EXPLOSION, mainSprite->getCenterX(), mainSprite->getY() + mainSprite->getH(), 5));


			this->soundManager->playSound(SOUND_EXPLOSION, 1500);

			//remove mine
			this->mineBombs[i]->~MineBomb();
			this->mineBombs.erase(this->mineBombs.begin() + i); 
			i--;

		}

		else if (this->mineBombs[i]->isOffScreen()) {

			//remove mines
			this->mineBombs[i]->~MineBomb();
			this->mineBombs.erase(this->mineBombs.begin() + i);

			i--;
		}

	}  

	//check for hits by enemy ships
	for (int i = 0; i < this->enemyShips.size(); i++) { 

		mainSprite = this->enemyShips[i]->getSprite();

		//check if hit player
		otherSprite = this->playerShip->getSprite();

		if (this->playerShip->isAlive() && mainSprite->collided(buffer, mainSprite->getW() / 6, mainSprite->getH() / 5, otherSprite, otherSprite->getW() / 100, otherSprite->getH()/4)) {
			
			int explosionType = (this->enemyShips[i]->getShipType() == ENEMY_SHIP_SMALL) ? MEDIUM_EXPLOSION : BIG_EXPLOSION;

			this->explosions.push_back(new Explosion(explosionType, mainSprite->getCenterX(), mainSprite->getCenterY(), 5));

			if (this->gameState->health - this->enemyShips[i]->getCollisionDamage() > 0)
				this->gameState->health -= this->enemyShips[i]->getCollisionDamage();
			else
				this->gameState->health = 0;



			this->soundManager->playSound(SOUND_EXPLOSION, 1000);

			//remove ship
			this->enemyShips[i]->~EnemyShip();
			this->enemyShips.erase(this->enemyShips.begin() + i);

			i--;
		}


		else if (this->enemyShips[i]->isOffScreen()) {

			//remove enemyShip
			this->enemyShips[i]->~EnemyShip();
			this->enemyShips.erase(this->enemyShips.begin() + i);

			i--;
		}


	}


}

void GameScreen::triggerReleases()
{	 

	//release mines
	if (clock() - lastmineReleaseTime > mineReleaseDelay) {
		this->mineBombs.push_back(new MineBomb((std::rand() % ((int)(PLAY_REGION_W - 10 * SCALING_FACTOR_RELATIVE_TO_1280))), -55 * SCALING_FACTOR_RELATIVE_TO_1280, 1));
		this->mineReleaseDelay = std::rand() % (3000) + 2000;
		lastmineReleaseTime = clock();
	}


	//release enemy
	if (clock() - lastEnemyReleaseTime > enemyReleaseDelay) {

		int shipType = (std::rand() % (5)<2) ? ENEMY_SHIP_SMALL : ENEMY_SHIP_BIG;
		this->enemyShips.push_back(new EnemyShip(shipType, &this->bullets, (std::rand() % ((int)(PLAY_REGION_W - 200 * SCALING_FACTOR_RELATIVE_TO_1280))), -55 * SCALING_FACTOR_RELATIVE_TO_1280, (shipType == ENEMY_SHIP_SMALL)?0.66:0.33));
		this->enemyReleaseDelay = std::rand() % (5000) + 2000;

		lastEnemyReleaseTime = clock(); 
	}

	
}