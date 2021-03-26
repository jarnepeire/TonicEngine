#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

enum SoundID : unsigned int
{
	PlayerScored,
	PlayerDied
};

struct PlayMessage
{
	PlayMessage() {}
	unsigned int ID{};
	float VolumePercentage{};
	float IsRequested{false};
};

class AudioSystem
{
public:
	AudioSystem() = default;
	virtual ~AudioSystem() = default;

	virtual void Update(float) {};
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

	void Update(float dt) override { if (m_pAudioSystem) m_pAudioSystem->Update(dt); }
	void Play(unsigned int id, float volumePercentage = 1.f) override
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
	void Update(float) override {}
	void Play(unsigned int, float) override { std::cout << "NullAudio\n"; }
};

