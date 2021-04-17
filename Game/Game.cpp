// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <TonicEngine.h>

int main()
{
    dae::TonicEngine engine;
    engine.Run();
    return 0;
}