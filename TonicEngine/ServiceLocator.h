#pragma once
#include "AudioSystem.h"
#include <mutex>

class ServiceLocator final
{
public:

	static AudioSystem& GetAudioSystem() { return *m_pAudioSystem; }
	static void RegisterAudioSystem(AudioSystem* pAudioSystem);

private:
	ServiceLocator();

	static std::mutex m_Mutex;
	static NullAudio m_pNullAudio;
	static AudioSystem* m_pAudioSystem;
};

