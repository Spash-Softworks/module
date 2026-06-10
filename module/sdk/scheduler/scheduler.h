#include "windows.h"
#include <string>

struct taskscheduler_t {
    uintptr_t get_datamodel(uintptr_t base);
	uintptr_t get_placeid(uintptr_t datamodel);
	uintptr_t get_scriptcontext(uintptr_t datamodel);
	int get_gameloaded(uintptr_t datamodel);


    uintptr_t get_job_by_name(uintptr_t base, const std::string& name);
};

inline taskscheduler_t* taskscheduler = nullptr;