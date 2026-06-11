//Dumped at      : 2026-06-04 07:10:54
//Dump duration  : 6.91 seconds

//Roblox version : version-ad5d3e2906444472
//Roblox         : 0.724.0.7240739
//This Dumper made by Versual
//(these are not checked)
//VannaRy Dumper

#pragma once
#include <cstdint>

#define REBASE(x) (x)
#define Hyperion_Rbase(x) (x)

namespace Offsets {
    namespace Internal_Offsets {
        const uintptr_t currfuncname = REBASE(0x4436E00);
        const uintptr_t lua_newstate = REBASE(0x4438D40);
        const uintptr_t pseudo2addr = REBASE(0x44351F0);
        const uintptr_t IdentityToCaps = REBASE(0x44A85F0);
        const uintptr_t atomic = REBASE(0x443B220);
        const uintptr_t ScriptContextResume = REBASE(0x1D67A90);
        // const uintptr_t markroot = 0x0;
        const uintptr_t pseudoaddr = REBASE(0x44351F0);
        const uintptr_t Print = REBASE(0x1DEC8F0);
        const uintptr_t std_runtime_error = REBASE(0x48B28F0);
        const uintptr_t GetGlobalState = REBASE(0x1C95970);
        const uintptr_t GetLuaStateForInstance = REBASE(0x1C95DD0);
        const uintptr_t GetCapabilites = REBASE(0x2FA7190);
        const uintptr_t GetLuaState = REBASE(0x62B730);
        const uintptr_t GetIdentityStruct = REBASE(0x44A81A0);
        const uintptr_t GetFastFlag = REBASE(0x67308B8);
        const uintptr_t GetValues = REBASE(0x1C90000);
        const uintptr_t GetPropertyData = REBASE(0x1D2E920);
        const uintptr_t Pushcclosure = REBASE(0x4432F40);
        // const uintptr_t Pushuserdata = 0x0;
        const uintptr_t RawScheduler = REBASE(0x18895BF);
        const uintptr_t TaskSchedulerTargetFps = REBASE(0x46DC8D0);
        // const uintptr_t TaskSynchronize = 0x0;
        const uintptr_t TaskDefer = REBASE(0x1DC8CC0);
        // const uintptr_t freegco = 0x0;
        const uintptr_t PushInstance = REBASE(0x1C891C0);
        const uintptr_t PushInstance_2 = REBASE(0x1C89200);
        const uintptr_t KTable = REBASE(0x7E91F70);
        // const uintptr_t FireTouchInterest = 0x0;
        const uintptr_t callerrfunc = REBASE(0x4435340);
        const uintptr_t auxopen = REBASE(0x35819A0);
        const uintptr_t freeudata = REBASE(0x4459C30);
        const uintptr_t newclasspage = REBASE(0x4458610);
        const uintptr_t newgcoblock = REBASE(0x4458220);
        const uintptr_t newpage = REBASE(0x4458710);
        // const uintptr_t f_luaopen = 0x0;
        const uintptr_t traversetable = REBASE(0x443D020);
        const uintptr_t loadsafe = REBASE(0x443D690);
        const uintptr_t close_state = REBASE(0x4438700);
        // const uintptr_t currentline = 0x0;
        const uintptr_t pusherror = REBASE(0x44362E0);
        const uintptr_t tag_error = REBASE(0x44386D0);
        // const uintptr_t propagetemark = 0x0;
        const uintptr_t FireProximityPrompt = REBASE(0x619F90);
        const uintptr_t compress = REBASE(0x493FEF0);
        const uintptr_t cocreate = REBASE(0x444A680);
        const uintptr_t coclose = REBASE(0x444A7A0);
        const uintptr_t lengthFieldBasedFrameDecoder = REBASE(0x69AA048);
        const uintptr_t AttachRobloxExtraSpace = REBASE(0x1CC3FD0);
        const uintptr_t OpcodeTable = 0x5F42790;
        const uintptr_t task_spawn = REBASE(0x1DC9BC0);
        const uintptr_t task_cancel = REBASE(0x1DC89E0);
        const uintptr_t task_delay = REBASE(0x1DC90F0);
        const uintptr_t task_defer = REBASE(0x1DC8CC0);
        const uintptr_t task_desynchronize = REBASE(0x1DC9330);
        const uintptr_t task_wait = REBASE(0x1DC9F30);
    }

    namespace Internal_Xref_Offsets {
    }

    namespace Dll_Offsets {
        const uintptr_t ControlFlowGuard = 0xF9BCE0;
        const uintptr_t BitMap = 0x3C548;
        const uintptr_t ByteShift = 0xF;
        const uintptr_t PageShift = 0xC;
        const uintptr_t BitMask = 0x7;
        const uintptr_t PageSize = 0x1000;
        const uintptr_t PageMask = 0xFFF;
    }

    namespace If_needed {
        constexpr uintptr_t ConnectionDisconnect = 0x1C9D600;
        constexpr uintptr_t IsLegalSendEvent = 0xA0D8B0;
    }

    namespace Lua_Offsets {
        // const uintptr_t Luau_Execute = 0x0;
        const uintptr_t LuaA_toobject = REBASE(0x4431BE0);
        const uintptr_t LuaD_Throw = REBASE(0x4436360);
        const uintptr_t luaB_print = REBASE(0x44495C0);
        const uintptr_t luaM_free = REBASE(0x4457F70);
        const uintptr_t luaM_freegco = REBASE(0x4457E10);
        const uintptr_t luaM_visitgco = REBASE(0x44584A0);
        const uintptr_t luaM_toobig = REBASE(0x443A7B0);
        const uintptr_t lua_newstate_path = REBASE(0x4438D40);
        const uintptr_t luaF_newUpval = REBASE(0x44614F0);
        const uintptr_t luaF_newtable = REBASE(0x4459AD0);
        // const uintptr_t luaF_freeUpval = 0x0;
        // const uintptr_t luaF_freethread = 0x0;
        const uintptr_t luaM_freearray = REBASE(0x4457F70);
        const uintptr_t luaS_newlstr = REBASE(0x44685C0);
        // const uintptr_t luaF_freeproto = 0x0;
        const uintptr_t luaG_runerrorL = REBASE(0x1DEC8F0);
        const uintptr_t luaF_newCclosure = REBASE(0x4461830);
        const uintptr_t luaF_newproto = REBASE(0x4461970);
        const uintptr_t luaO_str2d = REBASE(0x4467D80);
        const uintptr_t luaD_rawunprotected = REBASE(0x4436020);
        const uintptr_t luaL_errorL = REBASE(0x44376E0);
        const uintptr_t luaopen_os = REBASE(0x444D000);
        const uintptr_t LuaF_Newproto = REBASE(0x4461970);
        // const uintptr_t Luau_Load = 0x0;
        const uintptr_t LuaVM_Load = REBASE(0xB476B0);
        // const uintptr_t Lua_Load = 0x0;
        const uintptr_t luaB_assert = REBASE(0x4449D20);
        const uintptr_t luaC_Step = REBASE(0x443BDD0);
        const uintptr_t luaT_objtypename = REBASE(0x4458960);
        const uintptr_t luaO_chunkid = REBASE(0x44678B0);
        const uintptr_t luaopen_base = REBASE(0x444A490);
        // const uintptr_t luaopen_math = 0x0;
        const uintptr_t luaH_clone = REBASE(0x4459AD0);
        const uintptr_t luaV_gettable = REBASE(0x4463540);
        const uintptr_t luaL_register = REBASE(0x4437CD0);
        const uintptr_t luaL_findtable = REBASE(0x4437730);
        const uintptr_t luaL_checklstring = REBASE(0x4437A90);
        const uintptr_t luaL_argerrorL = REBASE(0x4437310);
        const uintptr_t luaL_typerrorL = REBASE(0x4438520);
        const uintptr_t luaH_new = REBASE(0x445A3D0);
        const uintptr_t lua_pushfstringL = REBASE(0x4433030);
        const uintptr_t lua_pushvfstring = REBASE(0x4433390);
        const uintptr_t luaF_newLclosure = REBASE(0x44618C0);
        const uintptr_t luaB_error = REBASE(0x44497E0);
        const uintptr_t luaB_gcinfo = REBASE(0x4449C10);
        const uintptr_t luaB_getfenv = REBASE(0x4449970);
        const uintptr_t luaB_getmetatable = REBASE(0x4449850);
        const uintptr_t luaB_net = REBASE(0x4449CC0);
        const uintptr_t luaB_newproy = REBASE(0x4449E70);
        const uintptr_t luaB_pcallrun = REBASE(0x444A2A0);
        const uintptr_t luaB_rawequal = REBASE(0x4449AB0);
        const uintptr_t luaB_rawget = REBASE(0x4449B00);
        const uintptr_t luaB_rawset = REBASE(0x4449B50);
        const uintptr_t luaB_rawlen = REBASE(0x4449BB0);
        const uintptr_t luaB_select = REBASE(0x1DBDE80);
        const uintptr_t luaB_setfenv = REBASE(0x44499D0);
        const uintptr_t luaB_setmetatable = REBASE(0x44498B0);
        const uintptr_t luaB_tonumber = REBASE(0x44496A0);
        const uintptr_t luaB_tostring = REBASE(0x4449E40);
        const uintptr_t luaB_type = REBASE(0x4449C40);
        const uintptr_t luaB_typeof = REBASE(0x4449C80);
        const uintptr_t luaB_pcally_alt = REBASE(0x444A390);
        // const uintptr_t lua_resetthread = 0x0;
        const uintptr_t lua_yield = REBASE(0x444A720);
        const uintptr_t luaV_settable = REBASE(0x4463B80);
        const uintptr_t luaV_lessthan = REBASE(0x4463DF0);
        const uintptr_t luaV_equal = REBASE(0x4463380);
        const uintptr_t lua_eception = REBASE(0x4435320);
        const uintptr_t luaT_init = REBASE(0x4458880);
    }

    namespace Raknet_Offsets {
        // const uintptr_t RakNet_Send = 0x0;
        const uintptr_t RakNet_ProcessNetworkPacket = REBASE(0x135C030);
        const uintptr_t RakNet_ReportNetworkError = REBASE(0x62D460);
    }

    namespace System {
        const uintptr_t Cache = 0xE8;
        const uintptr_t LRUCache = 0x20;
        const uintptr_t MeshData = 0x40;
        const uintptr_t AssetID = 0x10;
    }
}