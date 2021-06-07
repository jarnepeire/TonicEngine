#include "UggWrongwayComponent.h"

using namespace Tonic;
UggWrongwayComponent::UggWrongwayComponent(Tonic::GameObject* parent, UggWrongway type, unsigned int jumpSoundId)
    : HexJumpAIComponent(parent, 1.25f, jumpSoundId)
    , m_UggWrongway(type)
{
}

HexCoordinate UggWrongwayComponent::DetermineNextJump()
{
    if (m_UggWrongway == UggWrongway::Ugg)
    {
        //Ugg - Moves from bottom right to the left or top left
        int coinFlip = rand() % 2;

        //Moving to the right or top right
        int row = (coinFlip == 0) ? 0 : 1;
        int col = (coinFlip == 0) ? -1 : -1;

        HexCoordinate hc{ row, col };
        return hc;
    }
    else
    {
        //Wrongway - Moves from bottom left to the right or top right
        int coinFlip = rand() % 2;

        //Moving to the right or top right
        int row = (coinFlip == 0) ? 0 : 1;
        int col = (coinFlip == 0) ? 1 : 0;

        HexCoordinate hc{ row, col };
        return hc;
    }
}
