#pragma once
namespace Tonic 
{
	struct PlayMessage
	{
		PlayMessage() {}
		unsigned int ID{};
		float VolumePercentage{ 1.f };
		float IsRequested{ false };
	};

	class AudioSystem
	{
	public:
		AudioSystem(const AudioSystem& other) = delete;
		AudioSystem(AudioSystem&& other) = delete;
		AudioSystem& operator=(const AudioSystem& other) = delete;
		AudioSystem& operator=(AudioSystem&& other) = delete;
		virtual ~AudioSystem() = default;
		virtual void Play(unsigned int id, float volumePercentage = 1.f) = 0;

		//Adds a sound and returns the newly created sound ID for the given file
		virtual unsigned int AddSound(const char* filepath) = 0;

	protected:
		AudioSystem() = default;
	};
}