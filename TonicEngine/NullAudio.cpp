#include "TonicEnginePCH.h"
#include "NullAudio.h"

void Tonic::NullAudio::Play(unsigned int, float)
{
	std::cout << "NullAudio\n";
}

unsigned int Tonic::NullAudio::AddSound(const char*)
{
	return 0;
}
