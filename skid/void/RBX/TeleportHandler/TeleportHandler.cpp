#include "TeleportHandler.hpp"

#include "TaskScheduler/TaskScheduler.hpp"

#include <lua.h>
#include <lstate.h>
#include <lapi.h>
#include <lualib.h>

#include "RBX/RBX.hpp"
#include "Execution/Execution.hpp"

// example loadstring function
int loadstring(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TSTRING); // Check first arg = string

	const char* Script = lua_tostring(L, 1); // We get the first arg as a string
	const char* ChunkName = luaL_optstring(L, 2, "Base-LoadString"); // We get the 2nd arguement but 
	//if there is nothing there we fallback to 3rd arg

	std::string Bytecode = RBX::Execution::CompileScript(Script);
	if (Bytecode[0] == '\0' || Bytecode.empty()) {
		const char* errorMessage = Bytecode.c_str() + 1;

		// local func, err
		lua_pushnil(L); // compiled function / func
		lua_pushstring(L, errorMessage); // error message / err
		return 2;
	}

	if (luau_load(L, ChunkName, Bytecode.c_str(), Bytecode.length(), 0) != LUA_OK) {
		// local func, err
		lua_pushnil(L); // func
		lua_pushvalue(L, -2); // err
		return 2;
	}

	Closure* function = clvalue(luaA_toobject(L, -1));
	if (function && function->l.p) {
		RBX::Execution::SetProtoCapabilities(function->l.p, &RBX::MaxCapabilities);
	}

	lua_setsafeenv(L, LUA_GLOBALSINDEX, false);
	return 1;
}

void RBX::TeleportHandler::Reset()
{}

void RBX::TeleportHandler::InitializeExecutor(uintptr_t Datamodel)
{
	if (!Datamodel) {
		return;
	}

	if (RBX::TaskScheduler::GetPlaceId(Datamodel) == 0) {
		return;
	}

	while (RBX::TaskScheduler::GetGameLoadedStatus(Datamodel) == 15) {
		Sleep(100);
	}

	uintptr_t ScriptContext = RBX::TaskScheduler::GetScriptContext(Datamodel);
	if (!ScriptContext) {
		return;
	}

	uintptr_t Identity = 0, Script = 0;
	uintptr_t MainThread = RBX::TaskScheduler::GetGlobalState(ScriptContext, &Identity, &Script);
	if (!MainThread) {
		return;
	}

	lua_State* RobloxState = reinterpret_cast<lua_State*>(MainThread);
	if (!RobloxState) {
		return;
	}

	lua_State* ExecutorState = lua_newthread(RobloxState);

	RBX::ExecutorState = ExecutorState;

	RBX::TaskScheduler::SetIdentity(ExecutorState, 8, true);

	luaL_sandboxthread(ExecutorState);
	
	// registering functions
	lua_pushcfunction(ExecutorState, loadstring, 0);
	lua_setglobal(ExecutorState, "loadstring");

	// print("INJECTED")
	lua_getglobal(ExecutorState, "print");
	lua_pushstring(ExecutorState, "INJECTED");
	lua_call(ExecutorState, 1, 0);

	RBX::TaskScheduler::SendScript("print('From Execution')");
}

void RBX::TeleportHandler::Initialize()
{
	std::thread([]() {
		uintptr_t LastDatamodel = RBX::TaskScheduler::GetDatamodel();
		if (!LastDatamodel) {
			return;
		}

		TeleportHandler::InitializeExecutor(LastDatamodel);

		uintptr_t CurrentDatamodel = 0;

		while (true)
		{
			CurrentDatamodel = RBX::TaskScheduler::GetDatamodel();
			if (!CurrentDatamodel) {
				Sleep(10);
				continue;
			}

			if (CurrentDatamodel != LastDatamodel) 
			{
				uintptr_t PlaceId = RBX::TaskScheduler::GetPlaceId(CurrentDatamodel);

				if (PlaceId == 0) {
					TeleportHandler::Reset();
				}
				else if (PlaceId > 0) {
					TeleportHandler::Reset();

					while (RBX::TaskScheduler::GetGameLoadedStatus(CurrentDatamodel) == 15) {
						Sleep(100);
					}

					TeleportHandler::InitializeExecutor(CurrentDatamodel);
				}

				LastDatamodel = CurrentDatamodel;
			}

			Sleep(10);
		}

	}).detach();
}