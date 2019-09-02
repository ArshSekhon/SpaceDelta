#pragma once
#include <vector>
#include "Bullet.h"
#include "../Sprite.h"
#include "../constants.h"


class PlayerShip {

private:
	Sprite* shipSprite;
	int playerShipSize;
	std::vector<Bullet*>* bullets;
	bool keyUp;
	unsigned long lastBulletShootTime;
	int bulletShootDelay;
	bool wasSpaceUp = false; 
	bool dualBullets = false;

public:
	PlayerShip(std::vector<Bullet*>* bullets, int bulletShootDelay);
	~PlayerShip();
	void showShipAndHandleControls(BITMAP* buffer);
	Sprite* getSprite();

};