// GameThanol.cpp : This file contains the 'main' function. Program execution begins and ends there.

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <TonicEngine.h>
#include "QBertGame.h"
#include <iostream>

using namespace Tonic;
int main(int, char* [])
{
    //Seed random generator
    srand(static_cast<unsigned>(time(0)));

    QBertGame* pGame = new QBertGame();
    Tonic::TonicEngine engine;
    engine.Run(pGame);
    delete pGame;
    return 0;
}