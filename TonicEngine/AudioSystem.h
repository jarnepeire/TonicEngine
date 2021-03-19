#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class AudioSystem
{
public:
	virtual ~AudioSystem() = default;
	virtual void Play(unsigned int id, float volumePercentage = 1.f) = 0;
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

	void Play(unsigned int id, float volumePercentage = 1.f) override
	{
		std::cout << "Playing ID: " << id << ", at volume: " << volumePercentage << std::endl;
		m_pAudioSystem->Play(id, volumePercentage);
	}

private:
	AudioSystem* m_pAudioSystem;
};

class SDLAudio : public AudioSystem
{
public:
	SDLAudio();
	virtual ~SDLAudio();

	void Play(unsigned int id, float volume) override;
private:
	Mix_Chunk* m_pSound;

	void Initialize() {};
};


class NullAudio : public AudioSystem
{
public:
	virtual ~NullAudio() = default;
	void Play(unsigned int, float) override { std::cout << "NullAudio\n"; }
};

