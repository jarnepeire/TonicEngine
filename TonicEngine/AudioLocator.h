#pragma once
#include "NullAudio.h"

namespace Tonic
{
	class AudioLocator final
	{
	public:
		static AudioSystem& GetAudioSystem() { return *m_pAudioSystem; }
		static void RegisterAudioSystem(AudioSystem* pAudioSystem);

	private:
		AudioLocator();

		static NullAudio m_pNullAudio;
		static AudioSystem* m_pAudioSystem;
	};
}