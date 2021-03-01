#pragma once
#include "Transform.h"
#include "Subject.h"

namespace dae 
{
	class GameObject;
}

class Component
{
public:
	Component(dae::GameObject* parent);
	virtual ~Component() {}

	virtual void FixedUpdate(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	void SetPosition(const float x, const float y);
	std::unique_ptr<Subject>& GetSubject() { return m_pSubject; }

protected:
	dae::GameObject* m_pGameObject = nullptr;
	dae::Transform m_Transform;
	std::unique_ptr<Subject> m_pSubject;
};

