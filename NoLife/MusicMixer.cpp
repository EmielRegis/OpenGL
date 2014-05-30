#include "MusicMixer.h"


MusicMixer::MusicMixer()
{
	this->engine = irrklang::createIrrKlangDevice();
	this->myReceiver = new MySoundEndReceiver(this);
	properBackgroundMusic();

	gunSingleShotSource = engine->addSoundSourceFromFile("resources\\sounds\\effects\\guns\\mp5\\mp5_single_shot.mp3");;
	gunSeriesShotSource = engine->addSoundSourceFromFile("resources\\sounds\\effects\\guns\\mp5\\mp5_long_serie.mp3");;
	gunClipChangeSource = engine->addSoundSourceFromFile("resources\\sounds\\effects\\guns\\mp5\\mp5_clip_change.mp3");;
	
}


MusicMixer::~MusicMixer()
{
	engine->drop();
}

MusicMixer::MySoundEndReceiver::MySoundEndReceiver(MusicMixer *mixer)
{
	this->mixer = mixer;
}

void MusicMixer::MySoundEndReceiver::OnSoundStopped(irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData)
{
	int number = (rand() % 10) + 0;
	sound = this->mixer->engine->play2D(this->mixer->soundtrack[number], false, false, true);

	sound->setSoundStopEventReceiver(this);
}

void MusicMixer::properBackgroundMusic()
{
	soundtrack[0] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\black-end.mp3");
	soundtrack[1] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\bruce-accident.mp3");
	soundtrack[2] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\bruce-crimson.mp3");
	soundtrack[3] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\bruce-trumpets.mp3");
	soundtrack[4] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\judas-deal.mp3");
	soundtrack[5] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\judas-demonizer.mp3");
	soundtrack[6] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\maiden-angel.mp3");
	soundtrack[7] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\maiden-daughter.mp3");
	soundtrack[8] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\maiden-montsegur.mp3");
	soundtrack[9] = engine->addSoundSourceFromFile("resources\\sounds\\soundtrack\\percival-rozum.mp3");

	for (int i = 0; i < 10; i++)
	{
		soundtrack[i]->setDefaultVolume(0.5f);
	}
}

void MusicMixer::playBackgroundMusic()
{
	srand(time(NULL));

	int number = (rand() % 10) + 0;

	if (backgroundTrack)
	{
		if (!backgroundTrack->isFinished() || !backgroundTrack->getIsPaused())
		{
			backgroundTrack->setIsPaused(true);
		}

		backgroundTrack->drop(); 
		backgroundTrack = 0;
	}

	backgroundTrack = engine->play2D(soundtrack[number], false, false, true);

	backgroundTrack->setSoundStopEventReceiver(myReceiver, 0);
}

void MusicMixer::playGunShotSerie()
{
	gunSingleShot = engine->play2D(gunSingleShotSource);
}


float MusicMixer::getBackgroundMusicVolume()
{
	return this->backgroundTrack->getVolume();
}

void MusicMixer::muteBackgroundMusic()
{
	this->backgroundTrack->setVolume(0.0f);
}

void MusicMixer::enableBackgroundMusic()
{
	this->backgroundTrack->setVolume(1.0f);
}
