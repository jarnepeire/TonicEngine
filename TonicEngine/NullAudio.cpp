#include "TonicEnginePCH.h"
#include "NullAudio.h"

void NullAudio::Play(unsigned int, float)
{
	std::cout << "NullAudio\n";
}

unsigned int NullAudio::AddSound(const char*)
{
	return 0;
}
