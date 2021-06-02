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

	virtual void Initialize() override {}
	virtual void FixedUpdate(float dt) override {}
	virtual void Update(float dt) override {}
	virtual void Render() const override {}

	virtual void ResetLevel() = 0;
	void SetStartScore(int score);
	void SetStartLives(int nbLives);

protected:
	std::shared_ptr<dae::GameObject> m_pQBert;
};

