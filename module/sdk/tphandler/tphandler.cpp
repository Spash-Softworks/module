#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"

#include "tphandler.h"

#include "windows.h"
#include <string>
#include <chrono>

#include "sdk/scheduler/scheduler.h"

void tphandler_t::init(uintptr_t base)
{
	auto begin = std::chrono::steady_clock::now();

	uintptr_t datamodel = 		taskscheduler->get_datamodel(base);
    uintptr_t placeid 	= 		taskscheduler->get_placeid(datamodel);
	uintptr_t scriptcontext = 	taskscheduler->get_scriptcontext(datamodel);
	int gameloaded = 			taskscheduler->get_gameloaded(datamodel);

	// jobs
	uintptr_t hybridscripts = 	taskscheduler->get_job_by_name(base, "WaitingHybridScriptsJob");
	uintptr_t heartbeat = 		taskscheduler->get_job_by_name(base, "Heartbeat");
	uintptr_t renderjob = 		taskscheduler->get_job_by_name(base, "RenderJob");

	using printfunc = void(__cdecl*)(int, const char*, ...);
    auto print = reinterpret_cast<printfunc>(base + Offsets::Internal_Offsets::Print);

    print(1, "hyperion has been deleted");

    print(0, "");
    print(0, "datamodel @ 0x%llX", 		datamodel);
    print(0, "placeid @ 0x%llX", 		placeid);
    print(0, "scriptcontext @ 0x%llX", 	scriptcontext);
	print(0, "gameloaded @ %d", 		gameloaded);
    print(0, "");
	print(0, "WaitingHybridScriptsJob @ 0x%llX", 	hybridscripts);
    print(0, "Heartbeat @ 0x%llX", 					heartbeat);
    print(0, "RenderJob @ 0x%llX", 					renderjob);
	print(0, "");

    auto now = std::chrono::steady_clock::now();
    auto end = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count();
    print(0, "%s loaded in %llds", "femboyware", end);
}
