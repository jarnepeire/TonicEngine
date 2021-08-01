#pragma once
#include "AudioSystem.h"

namespace Tonic
{
	class LogAudio : public AudioSystem
	{
	public:
		LogAudio(AudioSystem* pAudioSystem);
		LogAudio(const LogAudio& other) = delete;
		LogAudio(LogAudio&& other) = delete;
		LogAudio& operator=(const LogAudio& other) = delete;
		LogAudio& operator=(LogAudio&& other) = delete;
		virtual ~LogAudio();

		void Play(unsigned int id, float volumePercentage = 1.f) override;
		unsigned int AddSound(const char* filepath) override;

	private:
		AudioSystem* m_pAudioSystem;
	};
}