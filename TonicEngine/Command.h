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

class FireCommand : public Command
{
public:
	FireCommand(dae::GameObject* object) : Command(object) {}
	virtual ~FireCommand() = default;
	void Execute() override;
};

class DuckCommand : public Command
{
public:
	DuckCommand(dae::GameObject* object) : Command(object) {}
	virtual ~DuckCommand() = default;
	void Execute() override;
};

class JumpCommand : public Command
{
public:
	JumpCommand(dae::GameObject* object) : Command(object) {}
	virtual ~JumpCommand() = default;
	void Execute() override;
};

class FartCommand : public Command
{
public:
	FartCommand(dae::GameObject* object) : Command(object) {}
	virtual ~FartCommand() = default;
	void Execute() override;
};

class MoveCommand : public Command
{
public:
	MoveCommand(dae::GameObject* object) : Command(object) {}
	virtual ~MoveCommand() = default;
	void Execute() override;
};

class FlyCommand : public Command
{
public:
	FlyCommand(dae::GameObject* object) : Command(object) {}
	virtual ~FlyCommand() = default;
	void Execute() override;
};



