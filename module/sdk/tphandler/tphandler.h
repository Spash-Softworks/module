#include "windows.h"
#include <string>

struct tphandler_t {
	void tphandler_t::setup(uintptr_t datamodel, uintptr_t scriptcontext, uintptr_t base);
    void init(uintptr_t base);
};

inline tphandler_t* tphandler = nullptr;