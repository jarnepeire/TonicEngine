#include "JumpToHexCommand.h"
#include <GameObject.h>
#include "HexJumpComponent.h"
#include "AudioLocator.h"
#include "RespawnComponent.h"
#include <iostream>

JumpToHexCommand::JumpToHexCommand(dae::GameObject* object, int rowJump, int colJump, int jumpSoundId)
	: Command(object)
	, m_RowJump(rowJump)
	, m_ColJump(colJump)
	, m_JumpSoundID(jumpSoundId)
{
}

void JumpToHexCommand::Execute()
{
	auto pHexJump = m_pObject->GetComponent<HexJumpComponent>();
	auto pRespawn = m_pObject->GetComponent<RespawnComponent>();

	//If we're still respawning, we can't do anything
	//and we can only jump to the next hex if we're standing still on a hex
	if (pHexJump && !pHexJump->IsJumping() && !pRespawn->IsRespawning())
	{
		pHexJump->JumpTo(m_RowJump, m_ColJump);
		AudioLocator::GetAudioSystem().Play(m_JumpSoundID, 0.15f);
	}
}

JumpToHexTopLeftCommand::JumpToHexTopLeftCommand(dae::GameObject* object, int jumpSoundId)
	: JumpToHexCommand(object, 1, -1, jumpSoundId)
{
}

JumpToHexBottomLeftCommand::JumpToHexBottomLeftCommand(dae::GameObject* object, int jumpSoundId)
	: JumpToHexCommand(object, -1, 0, jumpSoundId)
{
}

JumpToHexTopRightCommand::JumpToHexTopRightCommand(dae::GameObject* object, int jumpSoundId)
	: JumpToHexCommand(object, 1, 0, jumpSoundId)
{
}

JumpToHexBottomRightCommand::JumpToHexBottomRightCommand(dae::GameObject* object, int jumpSoundId)
	: JumpToHexCommand(object, -1, 1, jumpSoundId)
{
}
