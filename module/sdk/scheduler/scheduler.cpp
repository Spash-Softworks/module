#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"

#include "scheduler.h"
#include "sdk/execution/execution.h"

#include "windows.h"
#include <string>

#include <lobject.h>
#include <lstate.h>
#include <lapi.h>
#include <lualib.h>
#include <Luau/BytecodeBuilder.h>
#include <Luau/BytecodeUtils.h>
#include <Luau/Compiler.h>


uintptr_t taskscheduler_t::get_datamodel(uintptr_t base)
{
	uintptr_t fake_datamodel = *reinterpret_cast<uintptr_t*>(base + FakeDataModel::Pointer);
	if (!fake_datamodel) {
		return 0;
	}

	uintptr_t datamodel = *reinterpret_cast<uintptr_t*>(fake_datamodel + FakeDataModel::RealDataModel);
	if (!datamodel) {
		return 0;
    }

    return datamodel;
}

uintptr_t taskscheduler_t::get_placeid(uintptr_t datamodel)
{
    if (!datamodel) {
        return 0;
    }

    return *reinterpret_cast<uintptr_t*>(datamodel + ClassOffsets::DataModel::PlaceId);
}

uintptr_t taskscheduler_t::get_capabilities(int identity)
{
	uintptr_t result;
	switch (identity)
	{
	case 1:
	case 4:
		result = 0x2000000000000003LL;
	    break;
	case 3:
		result = 0x300000000000000BLL;
	    break;
	case 5:
		result = 0x2000000000000001LL;
	    break;
	case 6:
		result = 0x700000000000000BLL;
	    break;
	case 7:
	case 8:
		result = 0x200000000000003FLL;
	    break;
	case 9:
	case 0xD:
		result = 12;
	    break;
	case 0xA:
		result = 0x6000000000000003LL;
	    break;
	case 0xB:
		result = 0x2000000000000000LL;
	    break;
	case 0xC:
		result = 0x1000000000000000LL;
	    break;
	default:
		result = 0;
	    break;
	}
	   
	return result | 0x3FFFFFFFFFFF00LL;
}

uintptr_t taskscheduler_t::get_job_by_name(uintptr_t base, const std::string& name)
{
    uintptr_t scheduler = *reinterpret_cast<uintptr_t*>(base + TaskScheduler::Pointer);
    if (!scheduler) {
        return 0;
    }

    uintptr_t jobs_start = *reinterpret_cast<uintptr_t*>(scheduler + TaskScheduler::JobStart);
    if (!jobs_start) {
        return 0;
    }

    uintptr_t jobs_end = *reinterpret_cast<uintptr_t*>(scheduler + TaskScheduler::JobEnd);
    if (!jobs_end) {
        return 0;
    }

	uintptr_t result = 0;
    for (uintptr_t job_ptr = jobs_start; job_ptr < jobs_end; job_ptr += 0x10)
    {
        uintptr_t job = *reinterpret_cast<uintptr_t*>(job_ptr);
        if (!job) {
            continue;
        }

        const std::string& job_name = *reinterpret_cast<const std::string*>(job + TaskScheduler::JobName);
        if (job_name == name) {
			result = job;
			break;
        }
    }

    return result;
}

uintptr_t taskscheduler_t::get_specific_job_by_name(uintptr_t base, const std::string& target_job_name, uintptr_t offset, uintptr_t datamodel)
{
	uintptr_t scheduler = *reinterpret_cast<uintptr_t*>(base + TaskScheduler::Pointer);
	if (!scheduler) {
		return 0;
	}

	uintptr_t jobs_start = *reinterpret_cast<uintptr_t*>(scheduler + TaskScheduler::JobStart);
	if (!jobs_start) {
		return 0;
	}

	uintptr_t jobs_end = *reinterpret_cast<uintptr_t*>(scheduler + TaskScheduler::JobEnd);
	if (!jobs_end) {
		return 0;
	}

	uintptr_t result = 0;
	for (uintptr_t job_ptr = jobs_start; job_ptr < jobs_end; job_ptr += 0x10)
	{
		uintptr_t job = *reinterpret_cast<uintptr_t*>(job_ptr);
		if (!job) {
			continue;
		}

		const std::string& job_name = *reinterpret_cast<const std::string*>(job + TaskScheduler::JobName);
		if (job_name.empty()) {
			continue;
		}

		if (job_name == target_job_name) {
			uintptr_t instance = *reinterpret_cast<uintptr_t*>(job + offset);
			if (!instance) {
				continue;
			}

			uintptr_t possible_datamodel = *reinterpret_cast<uintptr_t*>(instance + Instance::Parent);
			if (!possible_datamodel) {
				continue;
			}

			if (possible_datamodel == datamodel) {
				result = job;
				break;
			}
		}
	}

	return result;
}

uintptr_t taskscheduler_t::get_scriptcontext(uintptr_t datamodel)
{
	if (!datamodel) {
		return 0;
	}

	uintptr_t children_ptr = *reinterpret_cast<uintptr_t*>(datamodel + Instance::Children);
	if (!children_ptr) {
		return 0;
	}

	uintptr_t children_start = *reinterpret_cast<uintptr_t*>(children_ptr);
	if (!children_start) {
		return 0;
	}

	uintptr_t children_end = *reinterpret_cast<uintptr_t*>(children_ptr + Instance::ChildrenEnd);
	if (!children_end) {
		return 0;
	}

	uintptr_t scriptcontext = 0;
	for (uintptr_t current = children_start; current < children_end; current += 0x10)
	{
		if (!current) {
			return 0;
		}

		uintptr_t child = *reinterpret_cast<uintptr_t*>(current);
		if (!child) {
			continue;
		}

		uintptr_t class_desc = *reinterpret_cast<uintptr_t*>(child + Instance::ClassDescriptor);
		if (!class_desc) {
			return 0;
		}

		const char* class_name = *reinterpret_cast<const char**>(class_desc + ClassDescriptor::ClassName);
		if (!class_name) {
			return 0;
		}

		if (std::string(class_name) == "ScriptContext") {
		    scriptcontext = child;
		    break;
		}
	}

	return scriptcontext;
}

int taskscheduler_t::get_gameloaded(uintptr_t datamodel) 
{
	if (!datamodel) {
		return 0;
	}

	return (*reinterpret_cast<uint8_t*>(datamodel + ClassOffsets::DataModel::GameLoaded)) != 0;
}

uintptr_t taskscheduler_t::get_globalstate(uintptr_t scriptcontext, uintptr_t* identity, uintptr_t* script)
{
	*reinterpret_cast<BOOLEAN*>(scriptcontext + ScriptContext::RequireBypass) = TRUE;

	using fn_t = uintptr_t(__fastcall*)(uintptr_t, uintptr_t*, uintptr_t*);
	static const auto fn = reinterpret_cast<fn_t>(
		reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)) + Offsets::Internal_Offsets::GetLuaStateForInstance);
	return fn(scriptcontext, identity, script);
}

void taskscheduler_t::set_identity(lua_State* thread, int identity, bool instant)
{
	if (!thread || !thread->userdata) return;

	const auto caps = get_capabilities(identity);
	auto* extra = reinterpret_cast<uint8_t*>(thread->userdata);
	*reinterpret_cast<int*>(extra + ExtraSpace::Identity) = identity;
	*reinterpret_cast<uintptr_t*>(extra + ExtraSpace::Capabilities) = caps;
}

void taskscheduler_t::execute(const std::string& script)
{
	if (!executor_state) return;

	std::string bytecode = compile_script(script);
	if (bytecode.empty() || bytecode[0] == '\0') return;

	int original_top = lua_gettop(executor_state);
	lua_State* thread = lua_newthread(executor_state);
	lua_pop(executor_state, 1);

	luaL_sandboxthread(thread);
	set_identity(thread, 8, false);

	if (luau_load(thread, "", bytecode.c_str(), bytecode.size(), 0) != LUA_OK) {
		lua_pop(thread, 1);
		return;
	}

	auto* closure = clvalue(luaA_toobject(thread, -1));
	set_proto_caps(closure->l.p, &max_caps);

	lua_getglobal(thread, "task");
	lua_getfield(thread, -1, "defer");
	lua_remove(thread, -2);
	lua_insert(thread, -2);

	if (lua_pcall(thread, 1, 0, 0) != LUA_OK)
		lua_pop(thread, 1);

	lua_settop(executor_state, original_top);
}