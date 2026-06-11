#include "execution.h"

#include <windows.h>
#include <Luau/Compiler.h>
#include <Luau/BytecodeBuilder.h>
#include <Luau/BytecodeUtils.h>
#include <Luau/Bytecode.h>

#include "sdk/update/offsets.hpp"

class opcode_encoder_t : public Luau::BytecodeEncoder
{
    void encode(uint32_t* data, size_t count) override
    {
        uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
        auto* table = reinterpret_cast<uint8_t*>(base + Offsets::Internal_Offsets::OpcodeTable);

        for (size_t i = 0; i < count;)
        {
            uint8_t op = LUAU_INSN_OP(data[i]);
            const auto len = Luau::getOpLength(static_cast<LuauOpcode>(op));
            data[i] = table[op * 227] | (data[i] & ~0xff);
            i += len;
        }
    }
} encoder;

std::string compile_script(const std::string& script)
{
    const char* mutable_globals[] = {
        "game", "Game", "workspace", "Workspace",
        "script", "shared", "_G", "_ENV", nullptr
    };

    Luau::CompileOptions opts{};
    opts.optimizationLevel = 1;
    opts.debugLevel = 2;
    opts.vectorLib = "Vector3";
    opts.vectorCtor = "new";
    opts.vectorType = "Vector3";
    opts.mutableGlobals = mutable_globals;

    return Luau::compile(script, opts, {}, &encoder);
}

void set_proto_caps(Proto* proto, uintptr_t* caps)
{
    proto->userdata = caps;
    for (int i = 0; i < proto->sizep; i++)
        set_proto_caps(proto->p[i], caps);
}
