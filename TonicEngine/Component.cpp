#include "TonicEnginePCH.h"
#include "Component.h"
#include "Subject.h"

Component::Component(dae::GameObject* parent)
	: m_pGameObject(parent)
	, m_pSubject(std::make_unique<Subject>())
{
}

void Component::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}