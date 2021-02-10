#pragma once
#include "Transform.h"

namespace dae 
{
	class GameObject;
}

class Component
{
public:
	Component(dae::GameObject* parent);
	virtual ~Component() {}

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	void SetPosition(const float x, const float y);

protected:
	dae::GameObject* m_pGameObject = nullptr;
	dae::Transform m_Transform;
};

