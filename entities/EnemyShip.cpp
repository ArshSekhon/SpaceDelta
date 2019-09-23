#include "EnemyShip.h"

EnemyShip::EnemyShip(int shipType, std::vector<Bullet*>* bullets, int initPosX, int initPosY, double skillLevel) {
	// initialize values
	this->shipType = shipType;
	this->bullets = bullets;
	// scale speed of the enemyship according to its skill level
	this->velY = this->velX = 30 * ((skillLevel * 1.0) / 10.0);
	// randomly chose horizontal direction of motion
	this->swervingLeft = std::rand() % (2);

	// create a new sprite object depending on the ship type
	if (this->shipType == ENEMY_SHIP_BIG)
		this->shipSprite = new Sprite(load_bitmap("assets/sprites/redbig.bmp", NULL),
			bigEnemyShipWidth, bigEnemyShipHeight,
			1, 8, 8, 10,
			velX, velY, 1, 1, 
			initPosX, initPosY, 1
		);
	else
		this->shipSprite = new Sprite(load_bitmap("assets/sprites/redsmallship.bmp", NULL),
			smallEnemyShipWidth, smallEnemyShipHeight,
			1, 5, 5, 10,
			velX, velY, 1, 1, 
			initPosX, initPosY, 1
		);
	// set a max cap of 10 on the skill level
	if (skillLevel > 10)
		skillLevel = 10;

	this->skillLevel = skillLevel;
}


EnemyShip::~EnemyShip() 
{
	//destroy sprite object
	this->shipSprite->~Sprite();
}

void EnemyShip::render(BITMAP* buffer)
{
	this->update(); 
	this->shipSprite->draw(buffer);
	this->showHealthBar(buffer);
}

void EnemyShip::update()
{ 
	// if ship is a small ship that doesnt shoots bullets just update its position and make it move
	if (shipType == ENEMY_SHIP_SMALL) 
	{
		this->shipSprite->move(SPRITE_MOVE_DOWN);
	}
	else
	{
		// if ship is a big ship capable of shooting bullets check if it is time to shoot a bullet
		if (clock() - lastBulletShot > enemyShootDelay) {
			// shoot a bullet
			lastBulletShot = clock();
			this->bullets->push_back(new Bullet(15 * SCALING_FACTOR_RELATIVE_TO_960, 35 * SCALING_FACTOR_RELATIVE_TO_960, 10 * SCALING_FACTOR_RELATIVE_TO_960, 8, this->shipSprite->getCenterX(), this->shipSprite->getY() + this->shipSprite->getH(), true, 20));
			// randomly set time for the next bullet shooting
			this->enemyShootDelay = std::rand() % (5000) + 500;

		}
		// make the ship move
		this->shipSprite->move(SPRITE_MOVE_DOWN);


		// make enemy ship go left and right to prevent it going off the screen
		if (this->swervingLeft) 
		{ 
			if (this->shipSprite->getX() < 10)
				swervingLeft = false;

			this->shipSprite->move(SPRITE_MOVE_LEFT);
		}
		else
		{
			if(this->shipSprite->getX() + this->shipSprite->getW() > PLAY_REGION_W*0.95)
			{
				
				swervingLeft = true;
			}

			this->shipSprite->move(SPRITE_MOVE_RIGHT);
		}

	}

}

int EnemyShip::getCollisionDamage()
{
	return (shipType == ENEMY_SHIP_BIG) ? bigShipCollisionDamage : smallShipCollisionDamage;
}

int EnemyShip::getW()
{
	return (shipType == ENEMY_SHIP_BIG) ? bigEnemyShipWidth : smallEnemyShipWidth;
}

int EnemyShip::getH()
{
	return (shipType == ENEMY_SHIP_BIG) ? bigEnemyShipHeight : smallEnemyShipHeight;
}

int EnemyShip::getX()
{
	return this->shipSprite->getX();
}

int EnemyShip::getY()
{
	return this->shipSprite->getY();
}

Sprite* EnemyShip::getSprite()
{
	return this->shipSprite;
}
	
int EnemyShip::getCenterX()
{
	return this->getX() + this->getW() / 2;
}

int  EnemyShip::getCenterY()
{
	return this->getY() + this->getH() / 2;
}

int EnemyShip::getShipType()
{
	return shipType;
}

void EnemyShip::showHealthBar(BITMAP* buffer) {
	
	// calculate the dimension and position of the health bar
	int healthBarW = 70 * SCALING_FACTOR_RELATIVE_TO_1280,
		healthBarH = 7 * SCALING_FACTOR_RELATIVE_TO_1280;
	int healthBarX1 = this->shipSprite->getX(),
		healthBarY1 = this->shipSprite->getY(),
		healthBarX2 = healthBarX1 + healthBarW * (1.0*health / 100.0),
		healthBarX2Full = healthBarX1 + healthBarW,
		healthBarY2 = healthBarY1 + healthBarH;

	// draw health bar
	rectfill(buffer, healthBarX1, healthBarY1, healthBarX2Full, healthBarY2, makecol(0, 0, 0));
	rectfill(buffer, healthBarX1, healthBarY1, healthBarX2, healthBarY2 , makecol(255, 0, 0));

}

int EnemyShip::makeBulletImpact(int impact)
{
	// update health accordin to the bullet impact value and the enemy skill level
	if(this->shipType == ENEMY_SHIP_BIG) 
		this->health -= (10.0 - 1.0 * this->skillLevel) / 20.0 * impact;
	else
		this->health -= (10.0 - 1.0 * this->skillLevel) / 10.0 * impact;



	if (this->health < 0)
		this->health = 0;

	return this->health;
}

bool EnemyShip::isOffScreen()
{
	return (this->shipSprite->getY() > SCREEN_H);

}