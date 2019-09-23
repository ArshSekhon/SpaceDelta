#pragma once
#include "../Sprite.h"
#include "../constants.h"
 

#define SMALL_EXPLOSION 0
#define MEDIUM_EXPLOSION 1
#define BIG_EXPLOSION 2
/**
 * @brief Represetns an explosion in the game
 * 
 */
class Explosion
{

private:
	/**
	 * @brief Pointer to the sprite object for explosion
	 * 
	 */
	Sprite* explosionSprite;
	
public:
	/**
	 * @brief Construct a new Explosion object
	 * 
	 * @param w Width of the explosion
	 * @param h Height of the explosion
	 * @param posX X-position of the explosion
	 * @param posY Y-position of the explosion
	 * @param fps Frames per Second for the explosion animation
	 */
	Explosion( int w, int h, int posX, int posY, int fps);
	/**
	 * @brief Construct a new Explosion object
	 * 
	 * @param size Predefined size for the explosion in range of 0-2 (Small to Big)
	 * @param posX X-position of the explosion
	 * @param posY Y-position of the explosion
	 * @param fps Frames per Second for the explosion animation
	 */
	Explosion( int size, int posX, int posY, int fps);
	/**
	 * @brief Renders the explosion to the bitmap
	 * 
	 * @param destination Bitmap to render the explosion on
	 */
	void renderExplosion(BITMAP* destination);
	/**
	 * @brief Checks if the animation for the explosion has ended
	 * 
	 * @return true If animation is complete
	 * @return false If animation is still in progress
	 */
	bool hasEnded();
	/**
	 * @brief Destroy the Explosion object
	 * 
	 */
	~Explosion();


};

