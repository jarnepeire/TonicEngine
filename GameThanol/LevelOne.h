#pragma once
#include "QBertScene.h"

namespace dae
{
	class GameObject;
}

class LevelOne : public QBertScene
{
public:
	LevelOne(const std::string& name, int idx);
	~LevelOne() = default;

	virtual void Initialize() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	void ResetLevel() override;

private:
	std::shared_ptr<dae::GameObject> m_pHexGridObject;

};

