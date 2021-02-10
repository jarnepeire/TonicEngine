#include "TonicEnginePCH.h"
#include "Component.h"

Component::Component(dae::GameObject* parent)
	: m_pGameObject(parent)
{
}

void Component::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}