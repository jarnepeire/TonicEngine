#include "TonicEnginePCH.h"
#include "Component.h"
#include "Subject.h"
#include "GameObject.h"

Tonic::Component::Component(Tonic::GameObject* parent)
	: m_pGameObject(parent)
	, m_pSubject(std::make_unique<Subject>())
{
}

void Tonic::Component::SetLocalPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

glm::vec3 Tonic::Component::GetWorldPosition() const
{
	return m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
}