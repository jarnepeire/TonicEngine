#include "TonicEnginePCH.h"
#include "LogAudio.h"

Tonic::LogAudio::LogAudio(AudioSystem* pAudioSystem)
	: m_pAudioSystem(pAudioSystem)
{
}

Tonic::LogAudio::~LogAudio()
{
	if (m_pAudioSystem) 
		delete m_pAudioSystem;
}

void Tonic::LogAudio::Play(unsigned int id, float volumePercentage)
{
	std::cout << "Playing ID: " << (int)id << ", at volume: " << volumePercentage << std::endl;
	m_pAudioSystem->Play(id, volumePercentage);
}

unsigned int Tonic::LogAudio::AddSound(const char*)
{
	return 0;
}

