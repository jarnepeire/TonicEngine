#include "TonicEnginePCH.h"
#include "AudioSystem.h"

SDLAudio::SDLAudio()
	: m_pSound(Mix_LoadWAV("../Data/door1.wav"))
{
}

SDLAudio::~SDLAudio()
{
	m_pSound = nullptr;
	Mix_FreeChunk(m_pSound);
}

void SDLAudio::Play(unsigned int, float volume)
{
	int sdlVolume = int(volume * (float)SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(m_pSound, sdlVolume);
	Mix_PlayChannel(0, m_pSound, 0);
}
