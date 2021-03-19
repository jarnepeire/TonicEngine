#include "TonicEnginePCH.h"
#include "ServiceLocator.h"

AudioSystem* ServiceLocator::m_pAudioSystem = nullptr;
NullAudio ServiceLocator::m_pNullAudio = NullAudio();
std::mutex ServiceLocator::m_Mutex = std::mutex();

ServiceLocator::ServiceLocator()
{
	m_pAudioSystem = &m_pNullAudio;
}

void ServiceLocator::RegisterAudioSystem(AudioSystem* pAudioSystem)
{
	std::lock_guard<std::mutex> lock{ m_Mutex };
	if (pAudioSystem)
		m_pAudioSystem = pAudioSystem;
}
