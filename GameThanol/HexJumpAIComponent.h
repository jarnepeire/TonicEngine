#pragma once
#include <Component.h>
#include "HexCoordinate.h"

namespace Tonic
{
	class GameObject;
}
class HexGrid;
class HexJumpComponent;

class HexJumpAIComponent : public Tonic::Component
{
public:
	HexJumpAIComponent(float postJumpWaitingTime, unsigned int jumpSoundId);
	virtual ~HexJumpAIComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float) override {}
	void Update(float dt) override;
	void Render() override {}

	bool IsActive() const { return m_IsActive; }
	void SetActive(bool b) { m_IsActive = b; }
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
	unsigned int m_JumpSoundID;
};

