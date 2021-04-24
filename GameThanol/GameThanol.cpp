// GameThanol.cpp : This file contains the 'main' function. Program execution begins and ends there.

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <TonicEngine.h>
#include "QBertGame.h"
#include <memory>

//#include <SDLAudio.h>

int main()
{
    //SDLAudio* pAudio = new SDLAudio();
    //delete pAudio;

    //QBertGame* pGame = new QBertGame();
    dae::TonicEngine engine;
    //engine.Run(pGame);
    engine.Run(nullptr);
    //delete pGame;
    return 0;
}