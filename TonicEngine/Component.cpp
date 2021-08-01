#include "TonicEnginePCH.h"
#include "Component.h"
#include "GameObject.h"
#include "Subject.h"

Tonic::Component::Component()
	: m_pGameObject(nullptr)
	, m_Transform()
	, m_pSubject(std::make_unique<Subject>())
	//, m_pSubject(new Subject())
{
}

Tonic::Component::~Component() = default;

void Tonic::Component::SetLocalPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

glm::vec3 Tonic::Component::GetWorldPosition() const
{
	return m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
}
