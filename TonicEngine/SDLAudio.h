#pragma once
#include "AudioSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include <unordered_map>
#include <mutex>

namespace Tonic
{


	class SDLAudio final : public AudioSystem
	{
	public:
		SDLAudio();
		virtual ~SDLAudio();

		void Play(unsigned int id, float volume) override;

		//Adds a sound and returns true if adding was succesfull, returns false if ID already exists
		bool AddSound(unsigned int eventId, const char* filepath);

		//Adds a sound and returns the newly created sound ID for the given file
		unsigned int AddSound(const char* filepath) override;

	private:
		//Ring Buffer
		int m_Head;
		int m_Tail;
		int m_MaxPending;
		std::vector<PlayMessage> m_Requests;

		//Sound
		float m_Timer;
		float m_IntervalSameSounds;

		int m_Channel;
		std::unordered_map<unsigned int, Mix_Chunk*> m_SoundsMap;

		//Threading
		std::mutex m_Mutex;
		std::condition_variable m_HasRequests;
		std::thread m_Thread;

		//Private functions
		void ProcessRequests();
		bool CanPlaySound(Mix_Chunk** storedSound, unsigned int id);
		void ResetDuplicateRequests();
		bool IsDuplicateRequest(unsigned int id);
	};

}
