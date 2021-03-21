#pragma once
#include "AudioSystem.h"
#include <unordered_map>

class SDLAudio : public AudioSystem
{
public:
	SDLAudio();
	virtual ~SDLAudio();

	void Update() override;
	void Play(Event id, float volume) override;

	void AddSound(Event eventId, const char* filepath);
private:
	std::unordered_map<Event, Mix_Chunk*> m_SoundsMap;

	//-1 means to grab whatever channel is currently available
	//other numbers are fixed channels to play sound on
	int m_Channel = -1;
};

