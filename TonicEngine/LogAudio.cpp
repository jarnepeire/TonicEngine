#include "TonicEnginePCH.h"
#include "LogAudio.h"

LogAudio::LogAudio(AudioSystem* pAudioSystem)
	: m_pAudioSystem(pAudioSystem)
{
}

LogAudio::~LogAudio()
{
	if (m_pAudioSystem) 
		delete m_pAudioSystem;
}

void LogAudio::Play(unsigned int id, float volumePercentage)
{
	std::cout << "Playing ID: " << (int)id << ", at volume: " << volumePercentage << std::endl;
	m_pAudioSystem->Play(id, volumePercentage);
}

unsigned int LogAudio::AddSound(const char*)
{
	return 0;
}

