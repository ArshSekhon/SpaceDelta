#pragma once
#include <vector>
#include "Bullet.h"
#include "../Sprite.h"
#include "../constants.h"
#include "../SoundManager.h"
#include "../assets/bmp_defines.h"

/**
 * @brief Used to represent player ship in the game
 * 
 */
class PlayerShip {

private:
	// pointer to the sprite object for Player ship
	Sprite* shipSprite;
	// size of player ship
	int playerShipSize;
	// pointer to the bullets vecto
	std::vector<Bullet*>* bullets;
	bool keyUp;
	// vars to keep track of when last bullet was shot and when the next bullet would be shot
	unsigned long lastBulletShootTime;
	int bulletShootDelay;
	// vars to hold some information regarding the Player ship
	bool wasSpaceUp = false; 
	bool dualBullets = false;
	bool isActive = true;
	//pointer to the sound manager (required for playing sound effects)
	SoundManager* soundManager;

	DATAFILE* sprites_datafile;

public:
	/**
	 * @brief Construct a new Player Ship object
	 * 
	 * @param sprites_datafile Pointer to the datafile object containing sprites
	 * @param bullets Pointer to the bullets vector
	 * @param bulletShootDelay Delay in milliseconds after which player can shoot 
	 * @param soundManager Pointer to the sound manager
	 */
	PlayerShip(DATAFILE* sprites_datafile, std::vector<Bullet*>* bullets, int bulletShootDelay, SoundManager* soundManager);
	/**
	 * @brief Destroy the Player Ship object
	 * 
	 */
	~PlayerShip();
	/**
	 * @brief Renders ship on the bitmap and handles the control of the ship from keyboard
	 * 
	 * @param buffer Bitmap where the player ship has to be rendered
	 */
	void showShipAndHandleControls(BITMAP* buffer);
	/**
	 * @brief Get the Sprite object for the player ship
	 * 
	 * @return Sprite* Pointer to the sprite object of the player ship
	 */
	Sprite* getSprite();
	/**
	 * @brief Mark the player ship as killed/destroyed
	 * 
	 */
	void kill();
	/**
	 * @brief Checks if player ship has been destroyed
	 * 
	 * @return true If player ship is alive
	 * @return false If player ship has been destroyed
	 */
	bool isAlive();

};