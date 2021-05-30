#pragma once
#include <Scene.h>
#include <string>

namespace dae
{
	class GameObject;
}

class QBertScene : public dae::Scene
{
public:
	QBertScene(const std::string& name, int idx);
	~QBertScene() = default;

	virtual void Initialize() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	void ResetLevel();

private:
	std::shared_ptr<dae::GameObject> m_pQBert;
};

