#pragma once
#include "AudioSystem.h"
#include <unordered_map>
#include <mutex>

class SDLAudio final : public AudioSystem
{
public:
	SDLAudio();
	virtual ~SDLAudio();

	void Update(float dt) override;
	void Play(unsigned int id, float volume) override;

	void ProcessRequests();

	//Adds a sound and returns true if adding was succesfull, returns false if ID already exists
	bool AddSound(unsigned int eventId, const char* filepath);
	unsigned int AddSound(const char* filepath);

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
};

