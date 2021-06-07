#include "TonicEnginePCH.h"
#include "AudioLocator.h"

Tonic::AudioSystem* Tonic::AudioLocator::m_pAudioSystem = nullptr;
Tonic::NullAudio Tonic::AudioLocator::m_pNullAudio = Tonic::NullAudio();

Tonic::AudioLocator::AudioLocator()
{
	m_pAudioSystem = &m_pNullAudio;
}

void Tonic::AudioLocator::RegisterAudioSystem(AudioSystem* pAudioSystem)
{
	if (pAudioSystem)
		m_pAudioSystem = pAudioSystem;
	else
		m_pAudioSystem = &m_pNullAudio;
}
