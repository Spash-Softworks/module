#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

#include <lobject.h>
#include <lstate.h>
#include <lapi.h>
#include <lualib.h>

#include <Luau/BytecodeBuilder.h>
#include <Luau/BytecodeUtils.h>
#include <Luau/Compiler.h>

#include "RBX.hpp"

namespace RBX::TaskScheduler
{
	uintptr_t GetDatamodel();

	uintptr_t GetScriptContext(uintptr_t Datamodel);
	uintptr_t GetPlaceId(uintptr_t Datamodel);
	int GetGameLoadedStatus(uintptr_t Datamodel);

	uintptr_t GetGlobalState(uintptr_t ScriptContext, uintptr_t* Identity, uintptr_t* Script);

	uintptr_t GetJobByName(std::string TargetJobName);
	uintptr_t GetSpecificJobByName(std::string TargetJobName, uintptr_t Offset, uintptr_t Datamodel);

	uintptr_t GetCapabilities(int Identity);
	void SetIdentity(lua_State* Thread, int Identity, bool IsInstance);

	void SendScript(const std::string& Script);
}