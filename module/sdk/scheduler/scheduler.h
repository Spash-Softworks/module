#include "windows.h"
#include <string>

struct lua_State;

struct taskscheduler_t {
    lua_State* executor_state = nullptr;

    uintptr_t get_datamodel(uintptr_t base);
	uintptr_t get_placeid(uintptr_t datamodel);
	uintptr_t get_scriptcontext(uintptr_t datamodel);
	uintptr_t get_capabilities(int identity);
	int get_gameloaded(uintptr_t datamodel);

	uintptr_t get_globalstate(uintptr_t scriptcontext, uintptr_t* identity, uintptr_t* script);
	void set_identity(lua_State* thread, int identity, bool instant);
	void execute(const std::string& script);

    uintptr_t get_job_by_name(uintptr_t base, const std::string& name);
    uintptr_t get_specific_job_by_name(uintptr_t base, const std::string& target_job_name, uintptr_t offset, uintptr_t datamodel);
};

inline taskscheduler_t* taskscheduler = nullptr;