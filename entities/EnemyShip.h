#pragma once
#include <vector>
#include "Bullet.h"
#include "../Sprite.h"
#include "../constants.h"
#include "../assets/bmp_defines.h"

#include <cstdlib>
#include <ctime>
 
#define ENEMY_SHIP_SMALL 0
#define ENEMY_SHIP_BIG 1

/**
 * @brief Used to represent and store information regarding the enemy ships in the game
 * 
 */

class EnemyShip {
public:
	/**
	 * @brief Construct a new Enemy Ship object
	 * 
	 * @param sprites_datafile Pointer to the datafile object containing sprites
	 * @param shipType Type of the ship: Pass ENEMY_SHIP_SMALL or 0 to create a smaller ship, Pass ENEMY_SHIP_BIG or 1 to create a bigger shipr ship
	 * @param bullets Pointer to vector used to store the bullets in the game
	 * @param initPosX Initial X-position of the Enemy
	 * @param initPosY Initial Y-position of the Enemy
	 * @param skillLevel The skill level of the Enemy
	 */
	EnemyShip(DATAFILE* sprites_datafile, int shipType, std::vector<Bullet*>* bullets, int initPosX, int initPosY, double skillLevel=0);
	/**
	 * @brief Destroy the Enemy Ship object
	 * 
	 */
	~EnemyShip();
	/**
	 * @brief Get the Sprite object for the EnemyShip
	 * 
	 * @return Sprite* Pointer to the sprite object for the EnemyShip
	 */
	Sprite* getSprite();
	/**
	 * @brief Render EnemyShip on the buffer
	 * 
	 * @param buffer the bitmap/buffer where the enemy ship should be rendered
	 */
	void render(BITMAP* buffer);
	/**
	 * @brief Gets the Collision Damage value for the enemy ship (the reduction it causes in player's health on collision)
	 * 
	 * @return int The collision damage value
	 */
	int getCollisionDamage();

	/**
	 * @brief Gets the width of the EnemyShip
	 * 
	 * @return int 
	 */
	int getW();
	/**
	 * @brief Gets the height of the EnemyShip
	 * 
	 * @return int 
	 */
	int getH();
	/**
	 * @brief Gets the X-Position of the EnemyShip
	 * 
	 * @return int 
	 */
	int getX();
	/**
	 * @brief Gets the Y-Position of the EnemyShip
	 * 
	 * @return int 
	 */
	int getY();

	/**
	 * @brief Gets the X-Position of the center of the EnemyShip
	 * 
	 * @return int 
	 */
	int getCenterX();
	/**
	 * @brief Gets the Y-Position of the center of the EnemyShip
	 * 
	 * @return int 
	 */
	int getCenterY();

	/**
	 * @brief Updates the health of the EnemyShip after an impact with a bullet or other object 
	 * 
	 * @param impactLevel The damage value of the bullet/ship that hits the Enemy Ship
	 * @return int The updated health of the enemy ship
	 */
	int makeBulletImpact(int impactLevel);

	/**
	 * @brief Get the Ship Type
	 * 
	 * @return int 
	 */
	int getShipType();
	/**
	 * @brief Checks if the Enemy Ship is off the screen
	 * 
	 * @return true If the Enemy Ship is outside the playing region/off-screen
	 * @return false If the Enemy Ship is still in the playing region/on-screen
	 */
	bool isOffScreen();
	 

private:
	// variable to store the type of enemy ship
	int shipType;
	// pointer to the sprite object for the Enemy
	Sprite* shipSprite;
	// variable to store the skill level
	double skillLevel ;

	DATAFILE* sprites_datafile;

	void update();	
	int health = 100;  

	// variable to store data regarding the timing for shooting bullets
	int enemyShootDelay = 0;
	unsigned long lastBulletShot = 0;

	// pointer to the vector used to store bullets in the game at a given time
	std::vector<Bullet*>* bullets;

	// scaled width and heights for the enemy ship
	const int smallEnemyShipWidth = 120 * SCALING_FACTOR_RELATIVE_TO_1280, 
			  smallEnemyShipHeight =  120 * SCALING_FACTOR_RELATIVE_TO_1280;
	const int bigEnemyShipWidth = 175 * SCALING_FACTOR_RELATIVE_TO_1280, 
			  bigEnemyShipHeight = 175 * SCALING_FACTOR_RELATIVE_TO_1280;

	// collision damage values for different ship types
	int bigShipCollisionDamage = 50;
	int smallShipCollisionDamage = 20;
	// variable to store if the enemyship is moving towards left or towards right
	bool swervingLeft = false;

	
	double velX = 3, velY = 3;
	int delayX = 1, delayY = 1;

	// function to render the health bar for the enemy
	void showHealthBar(BITMAP* buffer);
};