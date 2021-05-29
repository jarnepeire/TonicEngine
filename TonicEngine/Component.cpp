#include "TonicEnginePCH.h"
#include "Component.h"
#include "Subject.h"
#include "GameObject.h"

Component::Component(dae::GameObject* parent)
	: m_pGameObject(parent)
	, m_pSubject(std::make_unique<Subject>())
{
}

void Component::SetLocalPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

glm::vec3 Component::GetWorldPosition() const
{
	return m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
}