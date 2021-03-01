#pragma once
#include "Observer.h"

namespace dae
{
	class GameObject;
}
class TextComponent;

//Acts like a display for Player score
class ScoreDisplay : public Observer
{
public:
	//To create link it to an existing text component
	ScoreDisplay(const std::shared_ptr<TextComponent>& pTextComponent);

	//To make the display own a new text component
	ScoreDisplay(const std::shared_ptr<TextComponent>& pTextComponent, float x, float y);

	virtual ~ScoreDisplay() = default;
	void Notify(dae::GameObject* object, Event e) override;

private:
	std::shared_ptr<TextComponent> m_pScoreText;
};
