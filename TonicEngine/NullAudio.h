#pragma once
#include "AudioSystem.h"

class NullAudio : public AudioSystem
{
public:
	NullAudio() = default;
	virtual ~NullAudio() = default;
	void Play(unsigned int, float) override;
	unsigned int AddSound(const char* filepath) override;

};
