#pragma once

#include <Windows.h>

#include <lobject.h>
#include <lstate.h>
#include <lapi.h>
#include <lualib.h>

#include <Luau/BytecodeBuilder.h>
#include <Luau/BytecodeUtils.h>
#include <Luau/Compiler.h>

#include "RBX/TaskScheduler/TaskScheduler.hpp"

namespace RBX::Execution
{
	class bytecodeEncoder : public Luau::BytecodeEncoder {
		inline void encode(uint32_t* data, size_t count) override {
			for (auto i = 0; i < count;) {
				uint8_t op = LUAU_INSN_OP(data[i]);
				const auto opLength = Luau::getOpLength((LuauOpcode)op);
				const auto opcodeLookupTable = reinterpret_cast<BYTE*>(RBX::Offsets::Luau::OpCodeLookupTable);
				uint8_t newOp = op * 227;
				newOp = opcodeLookupTable[newOp];
				data[i] = (newOp) | (data[i] & ~0xff);
				i += opLength;
			}
		}
	};

	inline std::string CompileScript(const std::string& script)
	{
		bytecodeEncoder encoder;

		const char* mutableGlobals[] = {

			("Game"), ("Workspace"), ("game"), ("plugin"), ("script"), ("shared"), ("workspace"),
			("_G"), ("_ENV"), nullptr
		};

		Luau::CompileOptions options;
		options.debugLevel = 1;
		options.optimizationLevel = 1;
		options.mutableGlobals = mutableGlobals;
		options.vectorLib = "Vector3";
		options.vectorCtor = "new";
		options.vectorType = "Vector3";

		return Luau::compile(script, options, {}, &encoder);
	};

	inline void SetProtoCapabilities(Proto* proto, uintptr_t* capabilities)
	{
		if (!proto) return;

		proto->userdata = capabilities;

		for (int i = 0; i < proto->sizep; ++i) {
			SetProtoCapabilities(proto->p[i], capabilities);
		}
	}

	inline void ExecuteScript(lua_State* L, const std::string& script)
	{
		if (!L) return;
		if (script.empty()) return;

		const int originalTop = lua_gettop(L);
		auto executionThread = lua_newthread(L);
		lua_pop(L, 1);

		RBX::TaskScheduler::SetIdentity(executionThread, 8, true);

		lua_pushvalue(executionThread, LUA_GLOBALSINDEX);
		lua_setglobal(executionThread, ("_ENV"));

		auto bytecode = CompileScript(script);
		if (bytecode[0] == '\0' or bytecode.empty()) {
			const char* errorMessage = bytecode.c_str() + 1;

			lua_getglobal(executionThread, ("warn"));
			lua_pushstring(executionThread, errorMessage);
			lua_call(executionThread, 1, 0);

			return;
		}

		if (luau_load(executionThread, ("Void-Client"), bytecode.c_str(), bytecode.length(), 0) != LUA_OK)
		{
			const char* errorMessage = lua_tostring(executionThread, -1);

			lua_getglobal(executionThread, ("warn"));
			lua_pushstring(executionThread, errorMessage);
			lua_call(executionThread, 1, 0);

			return;
		}

		Closure* closure = clvalue(luaA_toobject(executionThread, -1));
		if (closure and closure->l.p)
			SetProtoCapabilities(closure->l.p, &RBX::MaxCapabilities);

		lua_getglobal(L, ("task"));
		lua_getfield(L, -1, ("defer"));
		lua_remove(L, -2);
		lua_xmove(executionThread, L, 1);

		if (lua_pcall(L, 1, 0, 0) != LUA_OK)
		{
			const char* errorMessage = lua_tostring(L, -1);

			lua_getglobal(L, ("warn"));
			lua_pushstring(L, errorMessage);
			lua_call(L, 1, 0);

			lua_pop(L, 1);

			return;
		}

		lua_settop(executionThread, 0);
		lua_settop(L, originalTop);
	}
}