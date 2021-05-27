#include "JumpToHexCommand.h"
#include <GameObject.h>
#include "HexJumpComponent.h"

JumpToHexCommand::JumpToHexCommand(dae::GameObject* object, int rowJump, int colJump)
	: Command(object)
	, m_RowJump(rowJump)
	, m_ColJump(colJump)
{
}

void JumpToHexCommand::Execute()
{
	auto pHexJump = m_pObject->GetComponent<HexJumpComponent>();
	if (pHexJump)
	{
		pHexJump->JumpTo(m_RowJump, m_ColJump);
	}
}

JumpToHexTopLeftCommand::JumpToHexTopLeftCommand(dae::GameObject* object)
	: JumpToHexCommand(object, 1, -1)
{
}

JumpToHexBottomLeftCommand::JumpToHexBottomLeftCommand(dae::GameObject* object)
	: JumpToHexCommand(object, -1, 0)
{
}

JumpToHexTopRightCommand::JumpToHexTopRightCommand(dae::GameObject* object)
	: JumpToHexCommand(object, 1, 0)
{
}

JumpToHexBottomRightCommand::JumpToHexBottomRightCommand(dae::GameObject* object)
	: JumpToHexCommand(object, -1, 1)
{
}
