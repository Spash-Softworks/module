#pragma once

#include <cstdint>
#include <Windows.h>
#include <memory>
#include <string>

struct lua_State;

#define REBASE(Address) (Address + reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)))

typedef enum { SUCCESS, YIELD, ERR } CoroutineResult;
namespace RBX
{
    struct LiveThreadRef {
        int _Refs;
        lua_State* thread;
        int32_t thread_ref;
        int32_t objectId;
    };


    struct WeakThreadRef
    {
        std::uint8_t pad_0[16];

        WeakThreadRef* previous; // 16
        WeakThreadRef* next; // 24
        LiveThreadRef* liveThreadRef; // 32
        struct Node_t* node; // 40

        std::uint8_t pad_1[8]; // 52
    };
    struct debugger_result_t {
        std::int32_t result;
        std::int32_t unk[0x4];
    };
}
// clear offsets
namespace Offsets
{
    const uintptr_t Print = REBASE(0x1C7BFE0);

    const uintptr_t RawScheduler = REBASE(0x801D408);
    const uintptr_t OpcodeLookupTable = REBASE(0x5f44cd0);
    const uintptr_t AppdataInfo = REBASE(0x7F6BED8);
    const uintptr_t LuaVMLoad = REBASE(0x19F1C60);


    const uintptr_t FireMouseClick = REBASE(0x226D130);
    const uintptr_t FireRightMouseClick = REBASE(0x226D2D0);
    const uintptr_t FireMouseHoverEnter = REBASE(0x226E6D0);
    const uintptr_t FireMouseHoverLeave = REBASE(0x226E870);
    const uintptr_t IsLegalSendEvent = REBASE(0xA13DE0); // 48 83 EC ? 48 8B 89 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 83 F8

    const uintptr_t FireTouchInterest = REBASE(0x2651870);
    const uintptr_t FireProximityPrompt = REBASE(0x22EB7E0);

    const uintptr_t TaskDefer = REBASE(0x1B5EE50);
    const uintptr_t ScriptContextResume = REBASE(0x1AAC8A0);

    const uintptr_t GetLuaStateForInstance = REBASE(0x19C3830);

    const uintptr_t CastArgs = REBASE(0x19CC2E0);

    const uintptr_t ConnectionDisconnect = REBASE(0x44AF820); // 48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 ? ? ? 48 85 D2

    namespace InstanceBridge {
        const uintptr_t Push = REBASE(0x1AB8A50);
    }
    namespace RobloxProperty {
        const uintptr_t GetRobloxPropertyData = REBASE(0xBFE000);
        const uintptr_t KTable = REBASE(0x787DA70);
    }
    namespace RobloxThread {
        const uintptr_t IdentityPtr = REBASE(0x79AD818);
        const uintptr_t GetTlsPointer = REBASE(0x92F0);
    }

    namespace Flags {
        const uintptr_t TaskSchedulerLimitTargetFpsTo240 = REBASE(0x7B45A48);
        const uintptr_t TaskSchedulerTargetFps = REBASE(0x787D9EC);
        const uintptr_t LockViolationInstanceCrash = REBASE(0x78F20A8);
        const uintptr_t LockViolationScriptCrash = REBASE(0x78F3718);
    }

    namespace Luau {
        const uintptr_t Luau_Execute = REBASE(0x3B513C0);
        const uintptr_t LuaO_NilObject = REBASE(0x5A46208);
        const uintptr_t LuaH_DummyNode = REBASE(0x5A458D8);
        const uintptr_t LuaC_Step = REBASE(0x3B4B650);
    }
    namespace Signal {
        constexpr uintptr_t next = 0x10;
        constexpr uintptr_t enabled = 0x20;
        constexpr uintptr_t signalSlot = 0x30;
        constexpr uintptr_t signalSlotWrapper = 0x38;
        namespace SignalSlotWrapper {
            constexpr uintptr_t Ptr = 0x10;
            constexpr uintptr_t secondPtr = 0x18;
            constexpr uintptr_t thirdPtr = 0x38;
        }
        namespace SignalSlot {
            constexpr uintptr_t isOnce = 0xB5;
            constexpr uintptr_t SignalRefs = 0x70;
            namespace Refs {
                constexpr uintptr_t luaThread = 0x8;
                constexpr uintptr_t luaThreadRefId = 0x10;
                constexpr uintptr_t functionRefId = 0x14;
            }
        }
        namespace WaitSlot {
            constexpr uintptr_t checkPointer = 0x10;
            constexpr uintptr_t connectionRefs = 0x38;
            constexpr uintptr_t connectionRefs2 = 0x40;
            constexpr uintptr_t connectionRefs3 = 0x50;
            constexpr uintptr_t threadRefContainer = 0x18;
            constexpr uintptr_t threadRefContainer2 = 0x8;
            constexpr uintptr_t threadRefContainer3 = 0x10;
            constexpr uintptr_t threadRef = 0x20;
        }
    }

    namespace Slot_wrapper {
        static auto weak_object_ref = 0x70;
        static auto function_id = 0x14;
        static auto thread_id = 0x10;
        static auto thread = 0x8;
    }

    namespace Connection {
        static auto next = 0x10;
        static auto enabled = 0x20;
        static auto slot_wrapper = 0x30;
        static auto slot_wrapper_self = 0x38;
    }

    namespace DataModel {
        const uintptr_t PlaceId = 0x198;
        const uintptr_t GameLoaded = 0x5F8;
        const uintptr_t FakeDataModelToDataModel = 0x1C0;
        const uintptr_t FakeDataModelPointer = REBASE(0x7F6C228);
    }

    namespace ScriptContext {
        const uintptr_t Face = 0x850;
        const uintptr_t RequireBypass = 0x948;
    }

    namespace BasePart {
        const uintptr_t Primitive = 0x148;
        namespace PrimitiveStructure {
            const uintptr_t Overlap = 0x200;
        }
    }
}

namespace Roblox
{
    inline auto Print = (uintptr_t(__fastcall*)(int, const char*, ...))Offsets::Print;

    inline auto TaskDefer = (int(__fastcall*)(lua_State*))Offsets::TaskDefer;
    inline auto Luau_Execute = (void(__fastcall*)(lua_State*))Offsets::Luau::Luau_Execute;
    inline auto GetTlsPointer = (void* (__fastcall*)(uintptr_t identityData))Offsets::RobloxThread::GetTlsPointer;
    inline auto GetLuaStateForInstance = (lua_State * (__fastcall*)(uint64_t, uint64_t*, uint64_t*))Offsets::GetLuaStateForInstance;

    inline auto GetRobloxPropertyData = (void* (__fastcall*)(uintptr_t, uintptr_t*, uintptr_t*, int))Offsets::RobloxProperty::GetRobloxPropertyData;
    inline auto KTable = reinterpret_cast<uintptr_t*>(Offsets::RobloxProperty::KTable);

    namespace InstanceBridge {
        inline auto UintPtr = (void(__fastcall*)(lua_State*, std::uintptr_t))Offsets::InstanceBridge::Push;
        inline auto Shared = (void(__fastcall*)(lua_State*, std::shared_ptr<std::uintptr_t*>))Offsets::InstanceBridge::Push;
        inline auto Void = (void(__fastcall*)(lua_State*, void**))Offsets::InstanceBridge::Push;
        inline auto Void2 = (void(__fastcall*)(lua_State*, void*))Offsets::InstanceBridge::Push;
        inline auto Weak = (void(__fastcall*)(lua_State*, std::weak_ptr<std::uintptr_t>))Offsets::InstanceBridge::Push;
    }

    inline auto LuaVM_Load = (int32_t(__fastcall*)(lua_State*, std::string*, const char*, int32_t))Offsets::LuaVMLoad;
    inline auto CastArgs = (uintptr_t(__fastcall*)(lua_State*, int, void*, bool, int))Offsets::CastArgs;
    inline auto isLegalSendEvent = (bool(__fastcall*)(uintptr_t*, uintptr_t*, uintptr_t))Offsets::IsLegalSendEvent;

    inline auto DisconnectConnection = (void(__fastcall*)(uintptr_t*))Offsets::ConnectionDisconnect;

    namespace Signals {
        inline auto FireProximityPrompt = (uintptr_t * (__thiscall*)(uintptr_t))Offsets::FireProximityPrompt;
        inline auto FireMouseClick = (void(__fastcall*)(__int64, float, __int64))Offsets::FireMouseClick;
        inline auto FireRightMouseClick = (void(__fastcall*)(__int64, float, __int64))Offsets::FireRightMouseClick;
        inline auto FireMouseHoverEnter = (void(__fastcall*)(__int64, __int64))Offsets::FireMouseHoverEnter;
        inline auto FireMouseHoverLeave = (void(__fastcall*)(__int64, __int64))Offsets::FireMouseHoverLeave;
        inline auto FireTouchInterest = (void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, bool, bool))Offsets::FireTouchInterest;
    }

    inline auto SCResume = (int(__fastcall*)(uintptr_t scriptContext, RBX::debugger_result_t*,
        RBX::LiveThreadRef**, int32_t nRet, bool isError,
        char const* errorMessage))Offsets::ScriptContextResume;
}