#include "QBertScene.h"
#include "CharacterComponent.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include "GameEvent.h"
#include "HexGrid.h"
#include "HexComponent.h"
#include "DiskComponent.h"
#include <RenderComponent.h>
#include <Renderer.h>
#include <SpriteComponent.h>
#include "GameLevelInfo.h"

using namespace Tonic;
QBertScene::QBertScene(const std::string& name, int idx, const std::wstring& levelFile)
	: Scene(name, idx)
	, m_pQBert(std::make_shared<GameObject>())
	, m_pSam(std::make_shared<GameObject>())
	, m_pSlick(std::make_shared<GameObject>())
	, m_pUgg(std::make_shared<GameObject>())
	, m_pWrongway(std::make_shared<GameObject>())
	, m_pHexGridObject(std::make_shared<GameObject>())
	, m_NbDisks()
	, m_pDisks()
	, m_DiskHexCoordinates()
	, m_pGameLevelInfo(std::make_shared<GameLevelInfo>(levelFile))
{
}

void QBertScene::SetStartScore(int score)
{
	auto pCharacter = m_pQBert->GetComponent<CharacterComponent>();
	if (pCharacter)
	{
		pCharacter->GainScore(score);
	}
}

void QBertScene::SetStartLives(int nbLives)
{
	auto pHealth = m_pQBert->GetComponent<HealthComponent>();
	if (pHealth)
	{
		pHealth->SetNbLives(nbLives);
	}
}

void QBertScene::AddDiskToGrid(std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc, unsigned int moveSoundId)
{
	auto pDisk = std::make_shared<GameObject>();

	auto pDiskComp = pDisk->AddComponent<DiskComponent>(std::make_shared<DiskComponent>(2.f, hexGrid, hc));
	pDiskComp->SetMovingSoundID(moveSoundId);

	auto pDiskSpriteComp = pDisk->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Props/Disk_Spritesheet.png", 16, 10, 4, 100));
	pDiskSpriteComp->SetLocalPosition(12, 6);

	pDisk->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	Add(pDisk);

	m_pDisks.push_back(pDisk);
	m_DiskHexCoordinates.push_back(hc);
	++m_NbDisks;
}
