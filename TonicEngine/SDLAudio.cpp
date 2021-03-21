#include "TonicEnginePCH.h"
#include "SDLAudio.h"

SDLAudio::SDLAudio()
{
}

SDLAudio::~SDLAudio()
{
	for (auto& it : m_SoundsMap)
	{
		it.second = nullptr;
		Mix_FreeChunk(it.second);
	}
}

void SDLAudio::Update()
{
	//Meaning there's no requests
	if (m_Head == m_Tail)
		return;

	//Play the earliest request, located at 'head'
	//Check if a sound is bound to the event first
	Event eventID = m_Requests[m_Head].EventID;
	Mix_Chunk* pSound = nullptr;
	if (m_SoundsMap.find(eventID) != m_SoundsMap.end())
		pSound = m_SoundsMap[eventID];
	else
		return;

	int sdlVolume = int(m_Requests[m_Head].VolumePercentage * (float)SDL_MIX_MAXVOLUME);
	Mix_VolumeChunk(pSound, sdlVolume);
	Mix_PlayChannel(m_Channel, pSound, 0);

	//We advance the 'head pointer' to the next element, or wrap it back around the buffer if needed
	m_Head = (m_Head + 1) % MAX_PENDING;
}

void SDLAudio::Play(Event eventID, float volume)
{
	//A fix for the issue of having 2 of the same sound requests causing a really loud effect
	//Check all pending requests for duplicates:
	for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
	{
		//Meaning we found a request with similar ID
		if (m_Requests[i].EventID == eventID)
		{
			//Take the largest volume of both requests
			m_Requests[i].VolumePercentage = max(volume, m_Requests[i].VolumePercentage);

			//We return, since the same request is still in the buffer about to be played
			return;
		}
	}

	//Meaning the max amount of requests are already pending
	if ((m_Tail + 1) % MAX_PENDING == m_Head)
	{
		//Double buffer size and copy over elements
		MAX_PENDING *= 2;
		m_Requests.resize(MAX_PENDING);
	}
		
	//Add new request to the end of the list.
	m_Requests[m_Tail].EventID = eventID;
	m_Requests[m_Tail].VolumePercentage = volume;

	//Move the tail 1 spot further or wrap the tail back around our fixed array if necessary, as our head advances too 
	//-> this is why it's called a ring buffer
	m_Tail = (m_Tail + 1) % MAX_PENDING;
}

void SDLAudio::AddSound(Event eventId, const char* filepath)
{
	Mix_Chunk* pSound = Mix_LoadWAV(filepath);
	m_SoundsMap.insert(std::pair<Event, Mix_Chunk*>(eventId, pSound));
}
