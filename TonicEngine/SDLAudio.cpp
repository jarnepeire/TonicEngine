#include "TonicEnginePCH.h"
#include "SDLAudio.h"

SDLAudio::SDLAudio()
	: m_Head(0)
	, m_Tail(0)
	//Start at 8 max requests at the same time
	, m_MaxPending(8)
	, m_Requests(m_MaxPending)
	, m_Timer(0.f)
	, m_IntervalSameSounds(0.05f)
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
			bool canPlay = true;

			//Check if a sound is bound to the event first
			unsigned int id = m_Requests[m_Head].ID;
			Mix_Chunk* pSound = nullptr;
			if (m_SoundsMap.find(id) != m_SoundsMap.end())
			{
				pSound = m_SoundsMap[id];

				//A fix for the issue of having 2 of the same sound requests causing a really loud effect
				//Reset the possibility for requests every "IntervalSameSounds" seconds
				if (m_Timer >= m_IntervalSameSounds)
				{
					m_Timer = 0.f; //Full reset needed! If we just subtract Interval, it can be possible the timer is still bigger next iteration
					for (int i = 0; i < m_MaxPending; ++i)
					{
						m_Requests[i].IsRequested = false;
					}
				}
				else
				{
					//Check all pending requests for duplicates:
					for (int i = 0; i < m_MaxPending; ++i)
					{
						if (m_Requests[i].ID == id && m_Requests[i].IsRequested)
						{
							//This sound has already been requested this frame, so dont proceed
							canPlay = false;
							break;
						}
					}
				}
			}
			else
			{
				//Else continue with next request, if there are any! We need to call a wait otherwise we can skip the wait call
				canPlay = false;
			}

			if (canPlay)
			{
				//If all went well, play the actual sound
				m_Requests[m_Head].IsRequested = true;
				int sdlVolume = int(m_Requests[m_Head].VolumePercentage * (float)SDL_MIX_MAXVOLUME);
				Mix_VolumeChunk(pSound, sdlVolume);
				Mix_PlayChannel(m_Channel, pSound, 0);
			}

			//We advance the 'head pointer' to the next element, or wrap it back around the buffer if needed
			m_Head = (m_Head + 1) % m_MaxPending;
		}

		//Meaning there's no requests, the head caught up with the tail so wait for new requests
		if (m_Head == m_Tail)
			m_HasRequests.wait(lock);

	} 	while (m_Head != m_Tail);
}

void SDLAudio::Update(float dt)
{
	m_Timer += dt;
}

void SDLAudio::Play(unsigned int id, float volume)
{
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
	m_HasRequests.notify_one();
}

bool SDLAudio::AddSound(unsigned int id, const char* filepath)
{
	//Sound ID is not used yet
	if (m_SoundsMap.find(id) == m_SoundsMap.end())
	{
		Mix_Chunk* pSound = Mix_LoadWAV(filepath);
		m_SoundsMap.insert(std::pair<unsigned int, Mix_Chunk*>(id, pSound));
		return true;
	}
	return false;
}

unsigned int SDLAudio::AddSound(const char* filepath)
{
	Mix_Chunk* pSound = Mix_LoadWAV(filepath);
	unsigned int id = (unsigned int)m_SoundsMap.size();
	m_SoundsMap.insert(std::pair<unsigned int, Mix_Chunk*>(id, pSound));
	return id;
}
