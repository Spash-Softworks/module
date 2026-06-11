#pragma once
#include <string>
#include <lobject.h>

inline uintptr_t max_caps = 0xFFFFFFFFFFFFFFFF;

std::string compile_script(const std::string& script);
void set_proto_caps(Proto* proto, uintptr_t* caps);
