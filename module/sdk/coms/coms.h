#include <windows.h>
#include <thread>
#include <vector>
#include <string>
#include <cstdint>
#include <atomic>

struct communication_t {
	void setup();
};

inline communication_t* server = nullptr;