#pragma once
#include "AudioSystem.h"
#include <unordered_map>
#include <mutex>

class SDLAudio final : public AudioSystem
{
public:
	SDLAudio();
	virtual ~SDLAudio();

	void Update() override;
	void Play(SoundID id, float volume) override;

	void ProcessRequests();
	void AddSound(SoundID eventId, const char* filepath);
private:
	int m_Head;
	int m_Tail;
	int m_MaxPending;
	std::vector<PlayMessage> m_Requests;

	int m_Channel;
	std::unordered_map<SoundID, Mix_Chunk*> m_SoundsMap;

	bool m_CanNotifyForRequest = false;
	std::mutex m_Mutex;
	std::condition_variable m_HasRequests;
	std::thread m_Thread;
};

