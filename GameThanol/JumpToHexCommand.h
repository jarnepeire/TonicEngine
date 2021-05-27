#pragma once
#include <Command.h>
#include <string>

class JumpToHexCommand : public Command
{
public:
	virtual ~JumpToHexCommand() = default;
	void Execute() override;

protected:
	JumpToHexCommand(dae::GameObject* object, int rowJump, int colJump);

private:
	int m_RowJump;
	int m_ColJump;
};

class JumpToHexTopLeftCommand : public JumpToHexCommand
{
public:
	JumpToHexTopLeftCommand(dae::GameObject* object);
	virtual ~JumpToHexTopLeftCommand() = default;
};

class JumpToHexBottomLeftCommand : public JumpToHexCommand
{
public:
	JumpToHexBottomLeftCommand(dae::GameObject* object);
	virtual ~JumpToHexBottomLeftCommand() = default;
};

class JumpToHexTopRightCommand : public JumpToHexCommand
{
public:
	JumpToHexTopRightCommand(dae::GameObject* object);
	virtual ~JumpToHexTopRightCommand() = default;
};

class JumpToHexBottomRightCommand : public JumpToHexCommand
{
public:
	JumpToHexBottomRightCommand(dae::GameObject* object);
	virtual ~JumpToHexBottomRightCommand() = default;
};
