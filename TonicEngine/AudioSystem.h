#pragma once

enum SoundID : unsigned int
{
	PlayerScored,
	PlayerDied
};

struct PlayMessage
{
	PlayMessage() {}
	unsigned int ID{};
	float VolumePercentage{1.f};
	float IsRequested{false};
};

class AudioSystem
{
public:
	virtual ~AudioSystem() = default;
	virtual void Play(unsigned int id, float volumePercentage = 1.f) = 0;

	//Adds a sound and returns the newly created sound ID for the given file
	virtual unsigned int AddSound(const char* filepath) = 0;

protected:
	AudioSystem() = default;
};

