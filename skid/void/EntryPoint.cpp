#include <Windows.h>
#include <thread>

#include "Visuals/Hook//Hook.hpp"
#include "RBX/TeleportHandler/TeleportHandler.hpp"

void Entry()
{
    RBX::Visuals::Initialize();

    RBX::TeleportHandler::Initialize();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD reason, LPVOID lpReserved )
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        std::thread(Entry).detach();
    }

    return TRUE;
}