#pragma once
#include "QBertScene.h"

class LevelTwo : public QBertScene
{
public:
	LevelTwo(const std::string& name, int idx);
	~LevelTwo() = default;

	virtual void Initialize() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	void ResetLevel() override;
};

