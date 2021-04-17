#include "TonicEnginePCH.h"
#include "AudioLocator.h"

AudioSystem* AudioLocator::m_pAudioSystem = nullptr;
NullAudio AudioLocator::m_pNullAudio = NullAudio();
//std::mutex AudioLocator::m_Mutex = std::mutex();

AudioLocator::AudioLocator()
{
	m_pAudioSystem = &m_pNullAudio;
}

void AudioLocator::RegisterAudioSystem(AudioSystem* pAudioSystem)
{
	//std::lock_guard<std::mutex> lock{ m_Mutex }; //Overkill 
	if (pAudioSystem)
		m_pAudioSystem = pAudioSystem;
	else
		m_pAudioSystem = &m_pNullAudio;
}
