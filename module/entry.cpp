/* 
    im gay.
	16:06 10/06/2026
*/

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <chrono>
#include <thread>

#include "sdk/tphandler/tphandler.h"

#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"
#include "sdk/coms/coms.h"



void emulation(HMODULE hModule)
{
    uintptr_t base 		= reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));

	tphandler->init(base);
    
    FreeLibrary(hModule);
}






BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        std::thread(emulation, hModule).detach();
		server->setup();
    }
    return TRUE;
}