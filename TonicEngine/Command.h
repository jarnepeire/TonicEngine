#pragma once
namespace dae 
{
	class GameObject;
}

class Command
{
public:
	Command(dae::GameObject* object)
	{
		m_pObject = object;
	}

	virtual ~Command() {}
	virtual void Execute() = 0;

protected:
	dae::GameObject* m_pObject;
};


class DieCommand : public Command
{
public:
	DieCommand(dae::GameObject* object, unsigned int soundId) 
		: Command(object) 
		, m_SoundID(soundId)
	{}
	virtual ~DieCommand() = default;
	void Execute() override;

private:
	unsigned int m_SoundID;
};

//Temporary command to fit the needs of this assignment
class ScoreCommand : public Command
{
public:
	ScoreCommand(dae::GameObject* object, unsigned int soundId)
		: Command(object) 
		, m_SoundID(soundId)
	{}
	virtual ~ScoreCommand() = default;
	void Execute() override;

private:
	unsigned int m_SoundID;
};

