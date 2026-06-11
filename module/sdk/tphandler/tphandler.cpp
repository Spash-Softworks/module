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
#include "sdk/execution/execution.h"

#include <lobject.h>
#include <lstate.h>
#include <lapi.h>
#include <lualib.h>

int loadstring(lua_state* L)
{
	luaL_checktype(L, 1, LUA_TSTRING);
  
  	const char* Script = lua_tostring(L, 1);
  	const char* ChunkName = luaL_optstring(L, 2, "Base-LoadString");
  
  	std::string bytecode = compile_script(Script);
  	if (bytecode[0] == '\0' || bytecode.empty()) {
  	    const char* err = bytecode.c_str() + 1;

  	    lua_pushnil(L);
  	    lua_pushstring(L, err);
  	    return 2;
  	}

  	if (luau_load(L, ChunkName, bytecode.c_str(), bytecode.length(), 0) != LUA_OK) {
  	    lua_pushnil(L);
  	    lua_pushvalue(L, -2);
  	    return 2;
  	}

  	Closure* function = clvalue(luaA_toobject(L, -1));
  	if (function && function->l.p) {
  	    set_proto_caps(function->l.p, &max_caps);
  	}
  	
  	lua_setsafeenv(L, LUA_GLOBALSINDEX, false);
  	return 1;
}

void tphandler_t::setup(uintptr_t datamodel, uintptr_t scriptcontext, uintptr_t base)
{
	if (!datamodel) {
		return;
	}

	if (taskscheduler->get_gameloaded(datamodel) == 0) {
		Sleep(100);
	}

	if (!scriptcontext) {
		return; 
	}

	uintptr_t identity = 0, script = 0;
	uintptr_t main_thread = taskscheduler->get_globalstate(scriptcontext, &identity, &script);
	if (!main_thread) {
		return;
	}

	lua_state* roblox_state = reinterpret_cast<lua_state *>(main_thread);
	if (!roblox_state) {
		return;
	}

	lua_state* executor_state = lua_newthread(roblox_state);
	taskscheduler->set_identity(executor_state, 8, true);
	taskscheduler->executor_state = reinterpret_cast<lua_State*>(executor_state);
	luaL_sandboxthread(executor_state);

	lua_pushcfunction(executor_state, loadstring, 0);
	lua_setglobal(executor_state, "loadstring");

	lua_getglobal(executor_state, "print");
	lua_pushstring(executor_state, "ratted");
	lua_call(executor_state, 1, 0);

	taskscheduler->execute("print('ratted')");


	int gameloaded = 			taskscheduler->get_gameloaded(datamodel);
	uintptr_t placeid 	= 		taskscheduler->get_placeid(datamodel);

	uintptr_t hybridscripts = 	taskscheduler->get_job_by_name(base, "WaitingHybridScriptsJob");
	uintptr_t heartbeat = 		taskscheduler->get_job_by_name(base, "Heartbeat");
	uintptr_t renderjob = 		taskscheduler->get_job_by_name(base, "RenderJob");

	using printfunc = void(__cdecl*)(int, const char*, ...);
    auto print = reinterpret_cast<printfunc>(base + Offsets::Internal_Offsets::Print);

    print(1, "hyperion has been deleted");

    print(0, "");
    print(0, "datamodel @ 0x%llX", 					datamodel);
    print(0, "placeid @ 0x%llX", 					placeid);
    print(0, "scriptcontext @ 0x%llX", 				scriptcontext);
	print(0, "gameloaded @ %d", 					gameloaded);
    print(0, "");
	print(0, "WaitingHybridScriptsJob @ 0x%llX", 	hybridscripts);
    print(0, "Heartbeat @ 0x%llX", 					heartbeat);
    print(0, "RenderJob @ 0x%llX", 					renderjob);
	print(0, "");

    auto now = std::chrono::steady_clock::now();
    auto end = std::chrono::duration_cast<std::chrono::seconds>(now - begin).count();
    print(0, "%s loaded in %llds", "femboyware", end);
}

void tphandler_t::init(uintptr_t base)
{
	auto begin = std::chrono::steady_clock::now();

	uintptr_t datamodel = 		taskscheduler->get_datamodel(base);
	uintptr_t scriptcontext = 	taskscheduler->get_scriptcontext(datamodel);

	tphandler->setup(datamodel, scriptcontext, base);
}