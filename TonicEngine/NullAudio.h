#pragma once
#include "AudioSystem.h"

namespace Tonic
{
	class NullAudio : public AudioSystem
	{
	public:
		NullAudio() = default;
		NullAudio();
		NullAudio(const NullAudio& other) = delete;
		NullAudio(NullAudio&& other) = delete;
		NullAudio& operator=(const NullAudio& other) = delete;
		NullAudio& operator=(NullAudio&& other) = delete;
		virtual ~NullAudio() = default;

		void Play(unsigned int, float) override;
		unsigned int AddSound(const char* filepath) override;
	};
}