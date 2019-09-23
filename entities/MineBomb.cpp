#include "./MineBomb.h" 

MineBomb::MineBomb( int initPosX, int initPosY, int difficultyLevel)
{	// initialize variables
	this->difficultyLevel = difficultyLevel;
	this->velY = this->velX = 30 * ((difficultyLevel * 1.0) / 10.0);
	// create a sprite object
	this->bombSprite = new Sprite(load_bitmap("assets/sprites/mines.bmp", NULL), this->size, this->size, 1, 2, 2, 2, this->velX, this->velY, this->delayX, this->delayY, initPosX, initPosY, 1);
	srand(time(NULL));
	// initialize variables with random values
	this->swerveDistance = std::rand()%(SCREEN_W/4);
	this->swervingLeft = std::rand() % (2);
	
	this->initX = initPosX;
	
}

MineBomb::MineBomb( int initPosX, int initPosY, double velX, double velY, int delayX, int delayY, int difficultyLevel) 
{
	// initialize variables
	this->velX = velX;
	this->velY = velY;
	this->delayX = delayX;
	this->delayY = delayY;
	// create a sprite object
	this->bombSprite = new Sprite(load_bitmap("assets/sprites/mines.bmp", NULL), this->size, this->size, 1, 2, 2, 2, this->velX, this->velY, this->delayX, this->delayY, initPosX, initPosY, 1);
	
}

MineBomb::~MineBomb() {
	// destruct the minebomb
	this->bombSprite->~Sprite();

}

void MineBomb::update() { 

	// update the position of the minebomb
	this->bombSprite->move(SPRITE_MOVE_DOWN);


	// change the direction of motion of the minebomb
	if (swervingLeft) {
		if (this->bombSprite->getCenterX() > initX - this->swerveDistance && this->bombSprite->getX() > 0)
			this->bombSprite->move(SPRITE_MOVE_LEFT);
		else 
		{
			swervingLeft = false;
		}
	}
	else {
		if (this->bombSprite->getCenterX() < initX + this->swerveDistance && this->bombSprite->getX() + this->bombSprite->getW() < PLAY_REGION_W)
			this->bombSprite->move(SPRITE_MOVE_RIGHT);
		else 
		{
			swervingLeft = true;
		}
	}


}
// render minebomb and update position
void MineBomb::render(BITMAP* buffer) {
	this->update();
	this->bombSprite->draw(buffer);
}

void MineBomb::setExploded() {
	this->exploded = true;
}

bool MineBomb::hasExploded() {
	return this->exploded;
}

Sprite* MineBomb::getSprite() {
	return this->bombSprite;
}
 
int MineBomb::getDamageVal()
{
	return damageVal;
}

void MineBomb::setDamageVal(int damageVal)
{
	this->damageVal = damageVal;
}

bool MineBomb::isOffScreen()
{
	return (this->bombSprite->getY() > SCREEN_H);
}