#pragma once
#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <functional>

namespace RBX::TeleportHandler
{
	void Reset();
	void InitializeExecutor(uintptr_t Datamodel);

	void Initialize();
}