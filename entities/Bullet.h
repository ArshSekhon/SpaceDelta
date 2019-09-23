#pragma once
#include "../Sprite.h"
#include "../constants.h"

/**
 * @brief Used to represent a bullet in the game (can be enemy or player bullet)
 * 
 */
class Bullet
{
private:
	// pointer to sprite object for the bullet
	Sprite* bulletSprite;
	int exploded; 
	// variable to store damage value of the bullet
	int damageVal = 10;
	 
public:
	/**
	 * @brief Construct a new Bullet object
	 * 
	 * @param w Width of the bullet when rendered on the screen
	 * @param h Height of the bullet when rendered on the screen
	 * @param speedY Number of pixels the bullet should move in Y-direction after delayY milliseconds have elasped
	 * @param delayY Delay between the update of position of the bullet in Y-direction
	 * @param posX Number of pixels the bullet should move in X-direction after delayX milliseconds have elasped
	 * @param posY Delay between the update of position of the bullet in X-direction
	 * @param isEnemyBullet Specifies if the bullet is an enemy bullet or bullet from player
	 * @param damageVal The value by which health of the ship decreases when hit by the bullet
	 */
	Bullet(int w, int h, double speedY, int delayY, int posX, int posY, bool isEnemyBullet = false, int damageVal = 20);
	/**
	 * @brief Destroy the Bullet object
	 * 
	 */
	~Bullet();
	/**
	 * @brief Renders the bullet to a bitmap
	 * 
	 * @param buffer Target bitmap where the bullet should be rendered
	 */
	void renderBullet(BITMAP* buffer);
	/**
	 * @brief Checks if the bullet is off the screen
	 * 
	 * @return true If the bullet is outside the playing region/off-screen
	 * @return false If the bullet is still in the playing region/on-screen
	 */
	bool isOffScreen();
	/**
	 * @brief Checks if the bullet has hit a target and has exploded
	 * 
	 * @return true If the bullet has already hit a target
	 * @return false If the bullet has not hit a target yet
	 */
	bool hasExploded();
	/**
	 * @brief Specifies if a bullet is an enemy bullet
	 * 
	 */
	bool isEnemyBullet;
	/**
	 * @brief Get the Sprite object
	 * 
	 * @return Sprite* The sprite object used for the bullet
	 */
	Sprite* getSprite();
	/**
	 * @brief Get the Damage Val object
	 * 
	 * @return int The damage that bullet causes on impact 
	 */
	int getDamageVal();
	/**
	 * @brief Set the Damage Val object
	 * 
	 * @param damageVal
	 */
	void setDamageVal(int damageVal);
};

