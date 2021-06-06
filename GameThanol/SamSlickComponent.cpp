#include "SamSlickComponent.h"
#include "HexJumpComponent.h"

SamSlickComponent::SamSlickComponent(dae::GameObject* parent)
    : HexJumpAIComponent(parent, 2.f)
{
}

HexCoordinate SamSlickComponent::DetermineNextJump()
{
    //Randomly determine to go down left or down right
    int coinFlip = rand() % 2;
    int row = -1;
    int col = (coinFlip == 0) ? 0 : 1;

    HexCoordinate hc{ row, col };
    return hc;
}
