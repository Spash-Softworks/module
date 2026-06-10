#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"
//
#include "scheduler.h"
//
#include "windows.h"
#include <string>

/// a small wrapper that avoids invalid memory reads
template<typename T>
static inline T get(uintptr_t addr, T fallback = T{}) {
    __try {
        return *reinterpret_cast<T*>(addr);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return fallback;
    }
}
///

uintptr_t taskscheduler_t::get_datamodel(uintptr_t base)
{
    uintptr_t fake_datamodel = get<uintptr_t>(base + FakeDataModel::Pointer);
    uintptr_t datamodel = get<uintptr_t>(fake_datamodel + FakeDataModel::RealDataModel);
    return datamodel;
}

uintptr_t taskscheduler_t::get_placeid(uintptr_t datamodel)
{
	return get<uintptr_t>(datamodel + ClassOffsets::DataModel::PlaceId);
}

uintptr_t taskscheduler_t::get_job_by_name(uintptr_t base, const std::string& name)
{
 	uintptr_t scheduler = get<uintptr_t>(base + TaskScheduler::Pointer);
    uintptr_t jobs_start = get<uintptr_t>(scheduler + TaskScheduler::JobStart);
    uintptr_t jobs_end = get<uintptr_t>(scheduler + TaskScheduler::JobEnd);

	if (!jobs_start || !jobs_end) return 0;
	
    for (uintptr_t job_ptr = jobs_start; job_ptr < jobs_end; job_ptr += 0x10)
    {
        uintptr_t job = get<uintptr_t>(job_ptr);
        if (!job) {
            continue;
        }

        const std::string& job_name = *reinterpret_cast<const std::string*>(job + TaskScheduler::JobName);
        if (job_name == name) {
			return job;
        }
    }

    return 0;
}

uintptr_t taskscheduler_t::get_scriptcontext(uintptr_t datamodel)
{
	uintptr_t children_ptr = get<uintptr_t>(datamodel + Instance::Children);
    uintptr_t children_start = get<uintptr_t>(children_ptr);
    uintptr_t children_end = get<uintptr_t>(children_ptr + Instance::ChildrenEnd);

	if (!children_start || !children_end) return 0;
	
	for (uintptr_t current = children_start; current < children_end; current += 0x10)
	{
		uintptr_t child = get<uintptr_t>(current);
        uintptr_t class_desc = get<uintptr_t>(child + Instance::ClassDescriptor);
        const char* class_name = get<const char*>(class_desc + ClassDescriptor::ClassName);

		if (class_name && std::string(class_name) == "ScriptContext") {
		    return child;
		}
	}

	return 0;
}

int taskscheduler_t::get_gameloaded(uintptr_t datamodel)
{
	return get<uint8_t>(datamodel + ClassOffsets::DataModel::GameLoaded) != 0;
}
