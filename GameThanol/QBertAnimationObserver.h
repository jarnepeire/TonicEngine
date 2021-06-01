#pragma once
#include <Observer.h>
#include <memory>

class SpriteComponent;
class QBertAnimationObserver : public Observer
{
public:
	QBertAnimationObserver() = default;
	QBertAnimationObserver(std::shared_ptr<SpriteComponent> spriteComponent);
	virtual ~QBertAnimationObserver() = default;

	void Notify(dae::GameObject * object, Event e) override;
	void SetSpriteComponent(std::shared_ptr<SpriteComponent> spriteComp) { m_SpriteComponent = spriteComp; }
private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
};

