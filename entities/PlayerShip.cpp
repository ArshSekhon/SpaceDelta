#include "PlayerShip.h" 

PlayerShip::PlayerShip(std::vector<Bullet*>* bullets, int bulletShootDelay, SoundManager* soundManager) {
	// initialize the vars
	this->soundManager = soundManager;
	this->bullets = bullets;
	this->bulletShootDelay = bulletShootDelay;
	this->playerShipSize = SCREEN_W * .15625 / 1.5; 
	double shipSpeed = 7 * ((SCREEN_W * 1.0) / 1280);
	// create sprite object
	this->shipSprite = new Sprite(
									load_bitmap("assets/sprites/player-spritesheet.bmp", NULL),
									playerShipSize, playerShipSize, // w, h
									1, 6,		// ssheetNumRows, ssheetNumCols
									6, 15,		// numOfFrames ,  frameDelay
									shipSpeed, shipSpeed, 12, 12,	// velX,  velY,  xDelay,  yDelay,
									(PLAY_REGION_W - playerShipSize) / 2, (SCREEN_H - (playerShipSize + 30))
								); 

}

PlayerShip::~PlayerShip() {
	// destroy the sprite object
	this->shipSprite->~Sprite();
}


void PlayerShip::showShipAndHandleControls(BITMAP* buffer) {
	// if ship has been destroyed -> don't need to do anything
	if (!isActive)
		return;

	// draw the sprite
	this->shipSprite->draw(buffer); 
	// handle movement controls: move left and move right 
	if (key[KEY_RIGHT] && (this->shipSprite->getX()+this->playerShipSize) < PLAY_REGION_W)
		this->shipSprite->move(SPRITE_MOVE_RIGHT);

	if (key[KEY_LEFT] && this->shipSprite->getX() > 0)
		this->shipSprite->move(SPRITE_MOVE_LEFT);
	

	// shoot a new bullet on space press
 	if (key[KEY_SPACE] && this->wasSpaceUp && (clock()-lastBulletShootTime)> this->bulletShootDelay) {

		this->lastBulletShootTime = clock();

		if (dualBullets) {
			this->bullets->push_back((Bullet*)new Bullet( 15 * SCALING_FACTOR_RELATIVE_TO_960, 35 * SCALING_FACTOR_RELATIVE_TO_960, 10 * SCALING_FACTOR_RELATIVE_TO_960, 8, this->shipSprite->getX() + this->playerShipSize / 2.3 -  this->playerShipSize / 4, this->shipSprite->getY()));

			this->bullets->push_back((Bullet*)new Bullet( 15 * SCALING_FACTOR_RELATIVE_TO_960, 35 * SCALING_FACTOR_RELATIVE_TO_960, 10 * SCALING_FACTOR_RELATIVE_TO_960, 8, this->shipSprite->getX() + this->playerShipSize / 2.3 + this->playerShipSize / 4, this->shipSprite->getY()));

		}
		else {
			this->bullets->push_back((Bullet*)new Bullet(15 * SCALING_FACTOR_RELATIVE_TO_960, 35 * SCALING_FACTOR_RELATIVE_TO_960, 10 * SCALING_FACTOR_RELATIVE_TO_960, 8, this->shipSprite->getX() + this->playerShipSize / 2.3, this->shipSprite->getY()));
		}

		// play laser shoot sound
		soundManager->playSound(SOUND_LASER_SHOOT, 1000);
	}

	this->wasSpaceUp = !key[KEY_SPACE];


}

bool PlayerShip::isAlive() 
{
	return this->isActive;
}

Sprite* PlayerShip::getSprite() {
	return this->shipSprite;
}

void PlayerShip::kill() {
	this->isActive = false;
}