#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Event.h"
#include <unordered_map>

struct PlayMessage
{
	PlayMessage() {}
	Event EventID{};
	float VolumePercentage{};
};

class AudioSystem
{
public:
	virtual ~AudioSystem() = default;
	virtual void Update() = 0;
	virtual void Play(Event id, float volumePercentage = 1.f) = 0;
};

class LogAudio : public AudioSystem
{
public:
	LogAudio(AudioSystem* pAudioSystem)
		: m_pAudioSystem(pAudioSystem)
	{}

	virtual ~LogAudio()
	{
		if (m_pAudioSystem) delete m_pAudioSystem;
	}

	void Update() override { m_pAudioSystem->Update(); }
	void Play(Event id, float volumePercentage = 1.f) override
	{
		std::cout << "Playing ID: " << (int)id << ", at volume: " << volumePercentage << std::endl;
		m_pAudioSystem->Play(id, volumePercentage);
	}

private:
	AudioSystem* m_pAudioSystem;
};

class NullAudio : public AudioSystem
{
public:
	virtual ~NullAudio() = default;
	void Update() override {}
	void Play(Event, float) override { std::cout << "NullAudio\n"; }
};

