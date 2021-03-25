#include "TonicEnginePCH.h"
#include "SDLAudio.h"

SDLAudio::SDLAudio()
	: m_Head(0)
	, m_Tail(0)
	, m_MaxPending(4)
	, m_Requests(m_MaxPending)
	//-1 means to grab whatever channel is currently available
	//other numbers are fixed channels to play sound on
	, m_Channel(-1)
	, m_SoundsMap()
	, m_Thread(std::thread([this]() { this->ProcessRequests(); }))
{
}

SDLAudio::~SDLAudio()
{
	//Clean up sound chunk pointers
	for (auto& it : m_SoundsMap)
	{
		it.second = nullptr;
		Mix_FreeChunk(it.second);
	}

	//Wake up thread so it can end
	m_HasRequests.notify_one();
	m_Thread.join();
}

void SDLAudio::ProcessRequests()
{
	//Play the earliest request, located at 'head'
	do
	{
		//Start lock here, we don't want the possibility for the m_Head to be changed and used as a thread goes over the code
		//Reason for unique_lock: works better with conditional variable for manual unlocking on notifies (ref: feedback ppt w07) 
		std::unique_lock<std::mutex> lock{ m_Mutex };
		if (m_Head != m_Tail)
		{
			//Check if a sound is bound to the event first
			SoundID id = m_Requests[m_Head].ID;
			Mix_Chunk* pSound = nullptr;
			if (m_SoundsMap.find(id) != m_SoundsMap.end())
				pSound = m_SoundsMap[id];
			else
				return;

			int sdlVolume = int(m_Requests[m_Head].VolumePercentage * (float)SDL_MIX_MAXVOLUME);
			Mix_VolumeChunk(pSound, sdlVolume);
			Mix_PlayChannel(m_Channel, pSound, 0);

			//We advance the 'head pointer' to the next element, or wrap it back around the buffer if needed
			m_Head = (m_Head + 1) % m_MaxPending;
		}

		//Meaning there's no requests, the head caught up with the tail
		if (m_Head == m_Tail)
			m_HasRequests.wait(lock);

	} 	while (m_Head != m_Tail);


}

void SDLAudio::Update()
{
	if (m_CanNotifyForRequest)
	{
		m_CanNotifyForRequest = false;
		m_HasRequests.notify_one();
	}
}

void SDLAudio::Play(SoundID id, float volume)
{
	//A fix for the issue of having 2 of the same sound requests causing a really loud effect
	//Check all pending requests for duplicates:
	for (int i = m_Head; i != m_Tail; i = (i + 1) % m_MaxPending)
	{
		//Meaning we found a request with similar ID
		if (m_Requests[i].ID == id)
		{
			//Take the largest volume of both requests
			m_Requests[i].VolumePercentage = max(volume, m_Requests[i].VolumePercentage);

			//We return, since the same request is still in the buffer about to be played
			return;
		}
	}

	//Best to start locking here, we don't want a double to double size twice, nor accidentally overwrite the future value in array
	std::lock_guard<std::mutex> lock{ m_Mutex };

	//Meaning the max amount of requests are already pending
	if ((m_Tail + 1) % m_MaxPending == m_Head)
	{
		//Double buffer size and copy over elements
		m_MaxPending *= 2;
		m_Requests.resize(m_MaxPending);
	}
		
	//Add new request to the end of the list.
	m_Requests[m_Tail].ID = id;
	m_Requests[m_Tail].VolumePercentage = volume;

	//Move the tail 1 spot further or wrap the tail back around our fixed array if necessary, as our head advances too 
	//-> this is why it's called a ring buffer
	m_Tail = (m_Tail + 1) % m_MaxPending;

	//Notify thread that a request happened
	m_CanNotifyForRequest = true;
	//m_HasRequests.notify_one();
}

void SDLAudio::AddSound(SoundID id, const char* filepath)
{
	Mix_Chunk* pSound = Mix_LoadWAV(filepath);
	m_SoundsMap.insert(std::pair<SoundID, Mix_Chunk*>(id, pSound));
}
