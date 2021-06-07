#pragma once
#include "Observer.h"

namespace Tonic
{
	class GameObject;
	class TextComponent;
}

//Acts like a display for Player health
class HealthDisplay : public Tonic::Observer
{
public:
	//To create link it to an existing text component
	HealthDisplay(const std::shared_ptr<Tonic::TextComponent>& pTextComponent);

	//To make the display own a new text component
	HealthDisplay(const std::shared_ptr<Tonic::TextComponent>& pTextComponent, float x, float y);

	virtual ~HealthDisplay() = default;
	void Notify(Tonic::GameObject* object, int eventId) override;

private:
	std::shared_ptr<Tonic::TextComponent> m_pHealthText;
};

