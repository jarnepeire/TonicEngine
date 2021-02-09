#include "TonicEnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "TonicEngine.h"

int main(int, char*[]) {
	dae::TonicEngine engine;
	engine.Run();
    return 0;
}