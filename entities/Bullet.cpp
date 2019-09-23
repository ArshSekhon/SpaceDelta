#include "Bullet.h"
// constructor
Bullet::Bullet(int w, int h, double speedY, int delayY, int posX, int posY, bool isEnemyBullet, int damageVal) {
	//set the exploded to false initially
	this->exploded = false;
	// create sprites for the bullets
	if(!isEnemyBullet)
		this->bulletSprite = new Sprite(load_bitmap("assets/sprites/bullet.bmp",NULL), 
									w, h, 
									1, 1, 1, 
									60, 
									0, speedY, 
									0, delayY, 
									posX, posY);
	else
		this->bulletSprite = new Sprite(load_bitmap("assets/sprites/bullet_red.bmp", NULL),
			w, h,
			1, 1, 1,
			60,
			0, speedY,
			0, delayY,
			posX, posY);
	// initializes the variables.
	this->isEnemyBullet = isEnemyBullet;
	this->damageVal = damageVal;

}
// destructors
Bullet::~Bullet() {
	this->bulletSprite->~Sprite();
}
// render the bullet on to the screen and update its position
void Bullet::renderBullet(BITMAP* buffer) {
	this->bulletSprite->draw(buffer);
	//update the position
	if(isEnemyBullet) 
		this->bulletSprite->move(SPRITE_MOVE_DOWN);
	else
		this->bulletSprite->move(SPRITE_MOVE_UP);

}

bool Bullet::isOffScreen() {
	int yCoord = this->bulletSprite->getY();
	return (yCoord > SCREEN_H || yCoord < 0);
}

bool Bullet::hasExploded() {
	return exploded;
}

Sprite* Bullet::getSprite() {
	return this->bulletSprite;
}

int Bullet::getDamageVal() 
{
	return damageVal;
}

void Bullet::setDamageVal(int damageVal)
{
	this->damageVal = damageVal;
}