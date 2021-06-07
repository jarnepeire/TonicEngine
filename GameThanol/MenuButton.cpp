#include "MenuButton.h"
#include "InputLocator.h"
#include "ImageComponent.h"

using namespace Tonic;
MenuButton::MenuButton(std::shared_ptr<ImageComponent> buttonComp, std::shared_ptr<ImageComponent> buttonHoverComp)
	: m_ButtonComp(buttonComp)
	, m_ButtonHoverComp(buttonHoverComp)
	, m_IsPressed(false)
	, m_IsHovered(false)
{
}

void MenuButton::Update(float)
{
	m_IsPressed = false;
	m_IsHovered = IsOverlappingButton();
	if (m_IsHovered)
	{
		m_ButtonComp->CanRender(false);
		m_ButtonHoverComp->CanRender(true);

		if (InputLocator::GetInputManager().IsMouseButtonDown(MouseButton::LMB, Tonic::TriggerState::Released))
		{
			//Is pressing
			m_IsPressed = true;
		}
	}
	else
	{
		m_ButtonComp->CanRender(true);
		m_ButtonHoverComp->CanRender(false);
	}
}

bool MenuButton::IsOverlappingButton()
{
	const auto& mousePos = InputLocator::GetInputManager().GetMousePos();
	glm::vec2 imagePos = m_ButtonComp->GetWorldPosition();
	float imageWidth = m_ButtonComp->GetImageWidth();
	float imageHeight = m_ButtonComp->GetImageHeight();

	if (mousePos.x > imagePos.x && mousePos.x < imagePos.x + imageWidth //overlaps horizonally
		&& mousePos.y > imagePos.y && mousePos.y < imagePos.y + imageHeight)  //overlaps vertically
		return true;

	return false;
}
