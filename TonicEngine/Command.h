#pragma once
namespace Tonic
{
	class GameObject;


	class Command
	{
	public:
		Command(Tonic::GameObject* object)
		{
			m_pObject = object;
		}

		virtual ~Command() {}
		virtual void Execute() = 0;

	protected:
		Tonic::GameObject* m_pObject;
	};
}
