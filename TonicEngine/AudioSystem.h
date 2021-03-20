#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

struct PlayMessage
{
	PlayMessage() {}
	unsigned int ID{};
	float VolumePercentage{};
};

//Works as Event Queue
class AudioSystem
{
public:
	virtual ~AudioSystem() = default;
	virtual void Update() = 0;
	virtual void Play(unsigned int id, float volumePercentage = 1.f) = 0;

protected:
	static int MAX_PENDING;
	static std::vector<PlayMessage> m_Requests;

	static int m_Head;
	static int m_Tail;
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

	void Update() override;
	void Play(unsigned int id, float volume) override;
private:
	Mix_Chunk* m_pSound;
};


class NullAudio : public AudioSystem
{
public:
	virtual ~NullAudio() = default;
	void Update() override {}
	void Play(unsigned int, float) override { std::cout << "NullAudio\n"; }
};

