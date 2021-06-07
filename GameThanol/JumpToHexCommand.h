#pragma once
#include <Command.h>
#include <string>

namespace Tonic
{
	class GameObject;
}

class JumpToHexCommand : public Tonic::Command
{
public:
	virtual ~JumpToHexCommand() = default;
	void Execute() override;

protected:
	JumpToHexCommand(Tonic::GameObject* object, int rowJump, int colJump, unsigned int jumpSoundId, unsigned int deathSoundId);

private:
	int m_RowJump;
	int m_ColJump;
	unsigned int m_JumpSoundID;
	unsigned int m_DeathSoundID;
};

class JumpToHexTopLeftCommand : public JumpToHexCommand
{
public:
	JumpToHexTopLeftCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId);
	virtual ~JumpToHexTopLeftCommand() = default;
};

class JumpToHexBottomLeftCommand : public JumpToHexCommand
{
public:
	JumpToHexBottomLeftCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId);
	virtual ~JumpToHexBottomLeftCommand() = default;
};

class JumpToHexTopRightCommand : public JumpToHexCommand
{
public:
	JumpToHexTopRightCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId);
	virtual ~JumpToHexTopRightCommand() = default;
};

class JumpToHexBottomRightCommand : public JumpToHexCommand
{
public:
	JumpToHexBottomRightCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId);
	virtual ~JumpToHexBottomRightCommand() = default;
};
