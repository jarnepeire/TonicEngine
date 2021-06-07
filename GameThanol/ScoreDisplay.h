#pragma once
#include "Observer.h"

namespace Tonic
{
	class GameObject;
	class TextComponent;
}


//Acts like a display for Player score
class ScoreDisplay : public Tonic::Observer
{
public:
	//To create link it to an existing text component
	ScoreDisplay(const std::shared_ptr<Tonic::TextComponent>& pTextComponent);

	//To make the display own a new text component
	ScoreDisplay(const std::shared_ptr<Tonic::TextComponent>& pTextComponent, float x, float y);

	virtual ~ScoreDisplay() = default;
	void Notify(Tonic::GameObject* object, int eventId) override;

private:
	std::shared_ptr<Tonic::TextComponent> m_pScoreText;
};
