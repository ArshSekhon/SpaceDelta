#include "SoundManager.h"

SoundManager::SoundManager(GameState* gameState) {
	this->gameState = gameState;
	sounds_datafile = load_datafile("assets/sounds.dat"); 
	//load music
	this->bgMusic = (MIDI*)sounds_datafile[MUSIC_MID].dat;
	// load sound samples
	//https://opengameart.org/content/laser-fire 
	this->laserSound = (SAMPLE*)sounds_datafile[LASER1_WAV].dat;
	//https://opengameart.org/content/big-explosion
	this->explosion = (SAMPLE*)sounds_datafile[EXPLOSION_WAV].dat;
	this->clickSound = (SAMPLE*)sounds_datafile[CLICK_WAV].dat;

	if (!laserSound || !explosion || !clickSound || !bgMusic) {		allegro_message("Error loading sounds.dat"); 	}   
 
}

SoundManager::~SoundManager() {
	unload_datafile(sounds_datafile); 
}

void SoundManager::playBgMusic(int loop) {
	
	if (this->gameState->bgMusicPlaying==1) {
		return;
	}

	if (play_midi(this->bgMusic, loop) == 0) {
		this->gameState->bgMusicPlaying = 1;
	}
	else {
		this->gameState->bgMusicPlaying = -1;
	}
}


void SoundManager::stopBgMusic(void)
{
	stop_midi();
	this->gameState->bgMusicPlaying = -1;
}

void SoundManager::playSound(int sfxId, int freq) {
	switch (sfxId) {
	case SOUND_CLICK:
		play_sample(clickSound, gameState->sound_volume * 12, 128, freq, 0);
		break; 
	case SOUND_LASER_SHOOT:
		play_sample(laserSound, gameState->sound_volume * 25.5, 128, freq, 0);
		break;
	case SOUND_EXPLOSION:
		play_sample(explosion, gameState->sound_volume * 25.5, 128, freq, 0);
		break;
	}
}
