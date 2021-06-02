#pragma once
#include "QBertScene.h"
class LevelThree : public QBertScene
{
public:
	LevelThree(const std::string& name, int idx);
	~LevelThree() = default;

	virtual void Initialize() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	void ResetLevel() override;

private:
	std::shared_ptr<dae::GameObject> m_pHexGridObject;
};

