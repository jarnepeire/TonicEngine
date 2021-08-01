#pragma once
namespace Tonic
{
	class GameObject;
	class Command
	{
	public:

		virtual ~Command() = default;

		/* Executes given command code */
		virtual void Execute() = 0;

	protected:
		Command(Tonic::GameObject* object)
		{
			m_pObject = object;
		}

		Tonic::GameObject* m_pObject;
	};
}
