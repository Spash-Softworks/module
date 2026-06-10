#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"

#include "tphandler.h"

#include "windows.h"
#include <string>

#include "sdk/scheduler/scheduler.h"

void tphandler_t::init(uintptr_t base)
{
	auto begin = std::chrono::steady_clock::now();

	uintptr_t datamodel = 		taskscheduler->get_datamodel(base);
    uintptr_t placeid 	= 		taskscheduler->get_placeid(datamodel);
	uintptr_t scriptcontext = 	taskscheduler->get_scriptcontext(datamodel);
	int gameloaded = 			taskscheduler->get_gameloaded(datamodel);

	using printfunc = void(__cdecl*)(int, const char*, ...);
    auto print = reinterpret_cast<printfunc>(base + Offsets::Internal_Offsets::Print);

    print(1, "hyperion has been deleted");

    print(0, "");
    print(0, "datamodel @ 0x%llX", 		datamodel);
    print(0, "placeid @ 0x%llX", 		placeid);
    print(0, "scriptcontext @ 0x%llX", 	scriptcontext);
	print(0, "gameloaded @ %d", 		gameloaded);
    print(0, "");
    
    auto now = std::chrono::steady_clock::now();
    auto end = std::chrono::duration_cast<std::chrono::seconds>(now - begin).count();
    print(0, "%s loaded in %llds", "femboyware", end);
}