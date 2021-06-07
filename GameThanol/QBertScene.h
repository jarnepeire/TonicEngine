#pragma once
#include <Scene.h>
#include <string>
#include "HexCoordinate.h"

namespace dae
{
	class GameObject;
}

class HexGrid;
class GameLevelInfo;
class QBertScene : public dae::Scene
{
public:
	QBertScene(const std::string& name, int idx, const std::wstring& levelFile);
	~QBertScene() = default;

	virtual void Initialize() override {}
	virtual void FixedUpdate(float dt) override {}
	virtual void Update(float dt) override {}
	virtual void Render() const override {}

	virtual void ResetLevel() = 0;
	void SetStartScore(int score);
	void SetStartLives(int nbLives);

	std::shared_ptr<dae::GameObject> GetHexGridObject() { return m_pHexGridObject; }
	std::shared_ptr<GameLevelInfo> GetGameLevelInfo() { return m_pGameLevelInfo; }
protected:
	std::shared_ptr<GameLevelInfo> m_pGameLevelInfo;
	std::shared_ptr<dae::GameObject> m_pQBert;

	std::shared_ptr<dae::GameObject> m_pSam;
	std::shared_ptr<dae::GameObject> m_pSlick;
	
	std::shared_ptr<dae::GameObject> m_pUgg;
	std::shared_ptr<dae::GameObject> m_pWrongway;

	std::shared_ptr<dae::GameObject> m_pHexGridObject;

	unsigned int m_NbDisks;
	std::vector<std::shared_ptr<dae::GameObject>> m_pDisks;
	std::vector<HexCoordinate> m_DiskHexCoordinates;

	void AddDiskToGrid(std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc, unsigned int moveSoundId);
};

