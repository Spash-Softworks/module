#pragma once

#include <cstdint>

/*
    Soda.lol CFG Dumper v1.1
    Made by Cabe

    Roblox Version: version-a182ba0d4c6f483b
    Dump Time: 57.42ms
    Total Offsets: 7
	*/

namespace Reversal
{
    static const uintptr_t ControlFlowGuard = 0x41CF10;
    static const uintptr_t BitMap = 0x14980D0;

    enum Offsets
    {
        ByteShift = 12,
        PageShift = 224,
        BitMask = 255,
        PageSize = 0x100000000,
        PageMask = 0xFFFFFFFF
    };
};
