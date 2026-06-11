#pragma once

#include <Windows.h>
#include <optional>
#include <queue>

#include <lualib.h>
#include <lobject.h>
#include <lstate.h>
#include <lapi.h>

namespace RBX
{
	inline uintptr_t MaxCapabilities = (0x200000000000003FLL | 0x3FFFFFFFFFFF00LL);

	inline lua_State* ExecutorState;
}