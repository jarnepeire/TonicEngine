#pragma once
#include <Command.h>
#include <string>

class JumpToHexCommand : public Command
{
public:
	virtual ~JumpToHexCommand() = default;
	void Execute() override;

protected:
	JumpToHexCommand(dae::GameObject* object, int rowJump, int colJump, int jumpSoundId);

private:
	int m_RowJump;
	int m_ColJump;
	int m_JumpSoundID;
};

class JumpToHexTopLeftCommand : public JumpToHexCommand
{
public:
	JumpToHexTopLeftCommand(dae::GameObject* object, int jumpSoundId);
	virtual ~JumpToHexTopLeftCommand() = default;
};

class JumpToHexBottomLeftCommand : public JumpToHexCommand
{
public:
	JumpToHexBottomLeftCommand(dae::GameObject* object, int jumpSoundId);
	virtual ~JumpToHexBottomLeftCommand() = default;
};

class JumpToHexTopRightCommand : public JumpToHexCommand
{
public:
	JumpToHexTopRightCommand(dae::GameObject* object, int jumpSoundId);
	virtual ~JumpToHexTopRightCommand() = default;
};

class JumpToHexBottomRightCommand : public JumpToHexCommand
{
public:
	JumpToHexBottomRightCommand(dae::GameObject* object, int jumpSoundId);
	virtual ~JumpToHexBottomRightCommand() = default;
};
