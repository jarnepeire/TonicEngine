#pragma once
#include <Component.h>
#include "HexCoordinate.h"

namespace dae
{
	class GameObject;
}
class HexGrid;
class HexJumpComponent;

class HexJumpAIComponent : public Component
{
public:
	HexJumpAIComponent(dae::GameObject* parent, float postJumpWaitingTime);
	virtual ~HexJumpAIComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override {}
	void Update(float dt) override;
	void Render() override {}

	bool IsActive() const { return m_IsActive; }
	void SetActive(bool b) { m_IsActive; }
	void StartWaiting();

	void ResetAI();
protected:
	virtual HexCoordinate DetermineNextJump() = 0;
	std::shared_ptr<HexJumpComponent> m_HexJumpComponent;

private:
	bool m_IsActive;

	bool m_CanWait;
	float m_WaitingTimer;
	float m_PostJumpWaitingTime;
};

