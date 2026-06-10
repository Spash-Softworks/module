#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"

#include "scheduler.h"

#include "windows.h"
#include <string>



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

	return *reinterpret_cast<bool*>(datamodel + ClassOffsets::DataModel::GameLoaded);
}