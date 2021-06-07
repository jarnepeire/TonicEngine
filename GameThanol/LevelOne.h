#pragma once
#include "QBertScene.h"
#include "HexCoordinate.h"
#include <vector>

namespace Tonic
{
	class GameObject;
}

class HexGrid;

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
};

