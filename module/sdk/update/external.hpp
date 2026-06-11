/* also known as external pointers in versual offsets */
#pragma once
#include <cstdint>

namespace FakeDataModel {
    inline constexpr uintptr_t Pointer = 0x78FF228;
    inline constexpr uintptr_t RealDataModel = 0x1D0;
}

namespace VisualEngine {
    inline constexpr uintptr_t Dimensions = 0xAB0;
    inline constexpr uintptr_t ViewMatrix = 0x150;
    inline constexpr uintptr_t RenderView = 0xBB0;
    inline constexpr uintptr_t Pointer = 0x801DFB0;
    inline constexpr uintptr_t FakeDataModel = 0xA90;
}

namespace TaskScheduler {
    inline constexpr uintptr_t JobEnd = 0xD0;
    inline constexpr uintptr_t JobName = 0x18;
    inline constexpr uintptr_t JobStart = 0xC8;
    inline constexpr uintptr_t MaxFPS = 0xB0;
    inline constexpr uintptr_t Pointer = 0x7E90548;
}

namespace Instance {
    inline constexpr uintptr_t ClassDescriptor = 0x18;
    inline constexpr uintptr_t Children = 0x78;
    inline constexpr uintptr_t ChildrenStart = 0x78;
    inline constexpr uintptr_t ChildrenEnd = 0x8;
    inline constexpr uintptr_t ChildrenStride = 0x10;
    inline constexpr uintptr_t Parent = 0x60;
}

namespace ExtraSpace {
    inline constexpr uintptr_t Identity     = 0x28; // TODO: verify
    inline constexpr uintptr_t Capabilities = 0x30; // TODO: verify
}

namespace ScriptContext {
    inline constexpr uintptr_t RequireBypass = 0x9E1;
}

namespace ChildrenVector {    inline constexpr uintptr_t Begin = 0x0;
    inline constexpr uintptr_t End = 0x8;
    inline constexpr uintptr_t Stride = 0x10;
}

namespace ClassDescriptor {
    inline constexpr uintptr_t ClassName = 0x8;
    inline constexpr uintptr_t Super = 0x10;
}
