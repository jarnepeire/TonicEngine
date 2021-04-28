#pragma once
#include <Command.h>
#include <string>

class ToSceneCommand : public Command
{
public:
	ToSceneCommand(const std::string& sceneName) 
		: Command(nullptr) 
		, m_SceneIdx(-1) 
		, m_SceneName(sceneName)
	{}
	
	ToSceneCommand(int sceneIdx) 
		: Command(nullptr) 
		, m_SceneIdx(sceneIdx)
		, m_SceneName("")
	{}

	virtual ~ToSceneCommand() = default;
	void Execute() override;

private:
	int m_SceneIdx;
	std::string m_SceneName;
};