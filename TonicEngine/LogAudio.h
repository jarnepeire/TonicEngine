#pragma once
#include "AudioSystem.h"

namespace Tonic
{


	class LogAudio : public AudioSystem
	{
	public:
		LogAudio(AudioSystem* pAudioSystem);
		virtual ~LogAudio();

		void Play(unsigned int id, float volumePercentage = 1.f) override;
		unsigned int AddSound(const char* filepath) override;

	private:
		AudioSystem* m_pAudioSystem;
	};
}