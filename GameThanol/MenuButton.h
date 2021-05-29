#pragma once
#include <memory>

class ImageComponent;
class MenuButton
{
public:
	MenuButton(std::shared_ptr<ImageComponent> buttonComp, std::shared_ptr<ImageComponent> buttonHoverComp);
	virtual ~MenuButton() = default;

	MenuButton(const MenuButton & other) = delete;
	MenuButton(MenuButton && other) noexcept = delete;
	MenuButton& operator=(const MenuButton & other) = delete;
	MenuButton& operator=(MenuButton && other) noexcept = delete;

	void Update(float dt);

	/* Returns the state of whether the button is pressed or not */
	const bool IsPressed() const { return m_IsPressed; }
	
private:
	std::shared_ptr<ImageComponent> m_ButtonComp;
	std::shared_ptr<ImageComponent> m_ButtonHoverComp;
	bool m_IsPressed;
	bool m_IsHovered;

	bool IsOverlappingButton();
};


