#include "TonicEnginePCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;
SpriteComponent::SpriteComponent(dae::GameObject* parent, const std::string& filename, int frameWidth, int frameHeight, int nbColumns, int animationSpeedInMS, float scale)
	: Component(parent)
	, m_EnableRender(true)
	, m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
	, m_Dest()
	, m_Src()
	, m_Flip(SDL_FLIP_NONE) // SDL_FLIP_HORIZONTAL // SDL_FLIP_NONE
	, m_FrameWidth(frameWidth)
	, m_FrameHeight(frameHeight)
	, m_Scale(scale)
	, m_NbColumns(nbColumns)
	, m_AnimationSpeedInMS(animationSpeedInMS)
	, m_CurrentAnimation(ESpriteAnimation::idle)
	, m_CurrentAnimationRow()
{
	auto pos = m_Transform.GetPosition();
	//Initialize src
	m_Src.x = 0;
	m_Src.y = 0;
	m_Src.w = m_FrameWidth;
	m_Src.h = m_FrameHeight;

	//Initialize dest
	m_Dest.x = static_cast<int>(pos.x);
	m_Dest.y = static_cast<int>(pos.y);
	m_Dest.w = m_Src.w * 2;
	m_Dest.h = m_Src.h * 2;
	
	//Apply scaling
	m_Dest.w = int((float)m_Dest.w * m_Scale);
	m_Dest.h = int((float)m_Dest.h * m_Scale);
}

void SpriteComponent::FixedUpdate(float)
{
}

void SpriteComponent::Update(float)
{
	//Set dest to current position
	const auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
	m_Dest.x = static_cast<int>(pos.x);
	m_Dest.y = static_cast<int>(pos.y);

	//Set the current row according to animation
	//int currentRow = static_cast<std::underlying_type<ESpriteAnimation>::type>(m_CurrentAnimation);
	//m_Src.y = 0 + (currentRow * m_FrameHeight);

	m_Src.y = 0 + (m_CurrentAnimationRow * m_FrameHeight);

	//Run over the different frames in a row
	m_Src.x = m_Src.w * static_cast<int>((SDL_GetTicks() / m_AnimationSpeedInMS) % m_NbColumns);
}

void SpriteComponent::Render()
{
	if (m_Texture != nullptr && m_EnableRender)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		pRender->RenderAnimation(*m_Texture, m_Src, m_Dest, m_Flip);
	}
}

void SpriteComponent::SetIsLeft(bool isLeft)
{
	m_Flip = (isLeft) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}
