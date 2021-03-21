#include "TonicEnginePCH.h"
#include "AudioSystem.h"

int AudioSystem::m_Head = 0;
int AudioSystem::m_Tail = 0;

int AudioSystem::MAX_PENDING = 1;
std::vector<PlayMessage> AudioSystem::m_Requests = std::vector<PlayMessage>{ (size_t)MAX_PENDING };