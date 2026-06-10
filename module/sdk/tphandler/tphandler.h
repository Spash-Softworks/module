#include "windows.h"
#include <string>

struct tphandler_t {
    void init(uintptr_t base);
};

inline tphandler_t* tphandler = nullptr;