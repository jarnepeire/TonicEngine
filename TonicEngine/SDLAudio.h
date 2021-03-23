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
	int m_Head;
	int m_Tail;
	int m_MaxPending;
	std::vector<PlayMessage> m_Requests;


	int m_Channel;
	std::unordered_map<Event, Mix_Chunk*> m_SoundsMap;
};

