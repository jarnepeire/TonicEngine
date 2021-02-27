#include "TonicEnginePCH.h"
#include "HealthComponent.h"
#include "TextComponent.h"

HealthComponent::HealthComponent(dae::GameObject* parent, int nbLives, const std::shared_ptr<TextComponent>& pTextComp)
	: Component(parent)
	, m_NbLives(nbLives)
	, m_pTextComponent(pTextComp)
	, m_DisplayText(true)
{
	m_pTextComponent->SetText("Lives: " + std::to_string(m_NbLives));
}

void HealthComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void HealthComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	m_pTextComponent->SetText("Lives: " + std::to_string(m_NbLives));
}

void HealthComponent::Render()
{
}

void HealthComponent::LoseLife()
{
	--m_NbLives;
}
