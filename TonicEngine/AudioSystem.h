#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

enum class SoundID : int
{
	PlayerScored,
	PlayerDied
};

struct PlayMessage
{
	PlayMessage() {}
	SoundID ID{};
	float VolumePercentage{};
};

class AudioSystem
{
public:
	AudioSystem() = default;
	virtual ~AudioSystem() = default;

	virtual void Update() {};
	virtual void Play(SoundID id, float volumePercentage = 1.f) = 0;
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
	void Play(SoundID id, float volumePercentage = 1.f) override
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
	void Play(SoundID, float) override { std::cout << "NullAudio\n"; }
};

