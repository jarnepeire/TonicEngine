#include "JumpToHexCommand.h"
#include <GameObject.h>
#include "HexJumpComponent.h"
#include "AudioLocator.h"
#include "RespawnComponent.h"
#include <iostream>

using namespace Tonic;
JumpToHexCommand::JumpToHexCommand(Tonic::GameObject* object, int rowJump, int colJump, unsigned int jumpSoundId, unsigned int deathSoundId)
	: Command(object)
	, m_RowJump(rowJump)
	, m_ColJump(colJump)
	, m_JumpSoundID(jumpSoundId)
	, m_DeathSoundID(deathSoundId)
{
}

void JumpToHexCommand::Execute()
{
	auto pHexJump = m_pObject->GetComponent<HexJumpComponent>();
	auto pRespawn = m_pObject->GetComponent<RespawnComponent>();

	//If we're still respawning, we can't do anything
	//and we can only jump to the next hex if we're standing still on a hex
	if (pHexJump && !pHexJump->IsJumping() && !pHexJump->IsBeingCarried() && !pRespawn->IsRespawning())
	{
		pHexJump->JumpTo(m_RowJump, m_ColJump);
		if (pHexJump->NeedsRespawn())
		{
			//Jumper fell off and lost a life
			AudioLocator::GetAudioSystem().Play(m_DeathSoundID, 0.15f);
		}
		else
		{
			//Jumper successfully jumped
			AudioLocator::GetAudioSystem().Play(m_JumpSoundID, 0.15f);
		}
		
	}
}

JumpToHexTopLeftCommand::JumpToHexTopLeftCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId)
	: JumpToHexCommand(object, 1, -1, jumpSoundId, deathSoundId)
{
}

JumpToHexBottomLeftCommand::JumpToHexBottomLeftCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId)
	: JumpToHexCommand(object, -1, 0, jumpSoundId, deathSoundId)
{
}

JumpToHexTopRightCommand::JumpToHexTopRightCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId)
	: JumpToHexCommand(object, 1, 0, jumpSoundId, deathSoundId)
{
}

JumpToHexBottomRightCommand::JumpToHexBottomRightCommand(Tonic::GameObject* object, unsigned int jumpSoundId, unsigned int deathSoundId)
	: JumpToHexCommand(object, -1, 1, jumpSoundId, deathSoundId)
{
}
