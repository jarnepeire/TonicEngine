#include "ToSceneCommand.h"
#include <SceneManager.h>

using namespace Tonic;
void ToSceneCommand::Execute()
{
	if (m_SceneIdx == -1)
	{
		SceneManager::GetInstance().SetActiveScene(m_SceneName);
	}
	else
	{
		SceneManager::GetInstance().SetActiveScene(m_SceneIdx);
	}
}
