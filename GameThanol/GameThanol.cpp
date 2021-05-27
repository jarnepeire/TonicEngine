// GameThanol.cpp : This file contains the 'main' function. Program execution begins and ends there.

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <TonicEngine.h>
#include "QBertGame.h"
#include <iostream>

int main(int, char* [])
{
    QBertGame* pGame = new QBertGame();
    dae::TonicEngine engine;
    engine.Run(pGame);
    delete pGame;
    return 0;
}