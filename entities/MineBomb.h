#pragma once
#include <cstdlib>
#include <ctime>
#include "../Sprite.h" 

/**
 * @brief Used to represent a mine bomb in the game
 * 
 */
class MineBomb
{
public:
	/**
	 * @brief Construct a new Mine Bomb object
	 * 
	 * @param initPosX Initial x-position of the minebomb
	 * @param initPosY Initial y-position of the minebomb
	 * @param difficultyLevel Difficulty level of the minebomb i.e. how hard it should be to avoid or destroy the minebomb 
	 */
	MineBomb(int initPosX, int initPosY, int difficultyLevel);
	/**
	 * @brief Construct a new Mine Bomb object
	 * 
	 * @param initPosX Initial x-position of the minebomb
	 * @param initPosY Initial y-position of the minebomb
	 * @param velX Number of pixels the bullet should move in X-direction after delayX milliseconds have elasped
	 * @param velY Number of pixels the bullet should move in Y-direction after delayY milliseconds have elasped
	 * @param delayX Delay between the update of position of the bullet in X-direction 
	 * @param delayY Delay between the update of position of the bullet in Y-direction
	 * @param difficultyLevel Difficulty level of the minebomb i.e. how hard it should be to avoid or destroy the minebomb 
	 */
	MineBomb(int initPosX, int initPosY, double velX, double velY, int delayX, int delayY, int difficultyLevel);
	/**
	 * @brief Destroy the Mine Bomb object
	 * 
	 */
	~MineBomb();
	/**
	 * @brief Update the position of the Minebomb
	 * 
	 */
	void update();
	/**
	 * @brief Render the Minebomb on a bitmap
	 * 
	 * @param buffer Bitmap where the MineBomb should be rendered on
	 */
	void render(BITMAP* buffer);
	/**
	 * @brief Set the explosion state
	 * 
	 */
	void setExploded();
	/**
	 * @brief Checks if the bullet has hit a target and has exploded
	 * 
	 * @return true If the bullet has already hit a target
	 * @return false If the bullet has not hit a target yet
	 */
	bool hasExploded();
	/**
	 * @brief Get the Sprite object for the MineBomb
	 * 
	 * @return Sprite* Pointer to the sprite object
	 */
	Sprite* getSprite();
	/**
	 * @brief Get the value of the Damage which MineBomb causes on impact
	 * 
	 * @return int The damage value for the minebomb
	 */
	int getDamageVal();
	/**
	 * @brief Set the value of the Damage which MineBomb causes on impact
	 * 
	 * @param damageVal The damage value for the minebomb
	 */
	void setDamageVal(int damageVal); 
	/**
	 * @brief Checks if the bullet is off the screen
	 * 
	 * @return true If the bullet is outside the playing region/off-screen
	 * @return false If the bullet is still in the playing region/on-screen
	 */
	bool isOffScreen();


private:
	//pointer to the sprite object for the minebomb
	Sprite* bombSprite;
	// variables to store other information regarding the MineBomb
	double difficultyLevel;
	double velX = 3, velY = 3;
	int delayX = 1, delayY = 1; 
	int initX = 0;
	int swerveDistance;
	
	bool swervingLeft = false;

	bool exploded = false; 
	int size = 50*SCALING_FACTOR_RELATIVE_TO_1280;
	int damageVal = 30;



};

