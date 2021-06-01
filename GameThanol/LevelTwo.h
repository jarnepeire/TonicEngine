#pragma once
#include <Scene.h>
class LevelTwo : public dae::Scene
{
public:
	LevelTwo(const std::string& name, int idx);
	~LevelTwo() = default;

	virtual void Initialize() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	void ResetLevel();

private:
	std::shared_ptr<dae::GameObject> m_pQBert;
	std::shared_ptr<dae::GameObject> m_pHexGridObject;
};

