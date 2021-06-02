#include "QBertScene.h"
#include "CharacterComponent.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include "Event.h"

using namespace dae;
QBertScene::QBertScene(const std::string& name, int idx)
	: Scene(name, idx)
	, m_pQBert(std::make_shared<GameObject>())
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
