#pragma once
#pragma comment(lib, "irrKlang\\irrKlang.lib")

#include <cstdlib>
#include <chrono>
#include "irrKlang\irrKlang.h"




class MusicMixer
{
public:
	MusicMixer();
	~MusicMixer();

protected:
	irrklang::ISoundEngine* engine;
	irrklang::ISound* backgroundTrack;
	irrklang::ISoundSource* soundtrack[10];

	void properBackgroundMusic();
	

	class MySoundEndReceiver : public irrklang::ISoundStopEventReceiver
	{
	protected:
		MusicMixer *mixer;

	public:
		MySoundEndReceiver(MusicMixer *mixer);
		virtual void OnSoundStopped(irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData);		
	};

	MySoundEndReceiver *myReceiver;


public:
	void playBackgroundMusic();
	
	float getBackgroundMusicVolume();
	void muteBackgroundMusic();
	void enableBackgroundMusic();
	
};

