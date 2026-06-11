#include "windows.h"
#include <string>
#include <vector>
#include <utility>

struct taskscheduler_t {
    uintptr_t get_datamodel(uintptr_t base);
	uintptr_t get_placeid(uintptr_t datamodel);
	uintptr_t get_scriptcontext(uintptr_t datamodel);
    uintptr_t get_job_by_name(uintptr_t base, const std::string& name);
	int get_gameloaded(uintptr_t datamodel);

    std::vector<std::pair<std::string, uintptr_t>> get_all_jobs(uintptr_t base);

	void execute(std::string& script);
};

inline taskscheduler_t* taskscheduler = nullptr;