#include <Exploit/Utils.hpp>
#include <Exploit/Globals.hpp>
#include <Communication/Communication.hpp>
#include <Exploit/TaskScheduler/TaskScheduler.hpp>
#include <Exploit/TeleportHandler/TeleportHandler.hpp>
#include <Exploit/Render/Render.hpp>
#include <shlobj.h>
#include <Windows.h>
#include <DbgHelp.h>
#include <Psapi.h>
#include <string>

#pragma comment(lib, "DbgHelp.lib")
#pragma comment(lib, "Psapi.lib")
LONG __stdcall ExceptionFilter(EXCEPTION_POINTERS* ExceptionInfo)
{
    const EXCEPTION_RECORD* ExcRecord = ExceptionInfo->ExceptionRecord;
    CONTEXT* Context = ExceptionInfo->ContextRecord;

    if (ExcRecord->ExceptionAddress == nullptr)
        return EXCEPTION_CONTINUE_SEARCH;

    constexpr DWORD SkipCodes[] = { 0x40010006, 0x4001000A, 0x406D1388, 0xE06D7363, 0x80000003, 0xC000001D, 0x80000004 };
    for (DWORD Code : SkipCodes)
        if (ExcRecord->ExceptionCode == Code)
            return EXCEPTION_CONTINUE_SEARCH;

    const char* ExceptionType;
    switch (ExcRecord->ExceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION:       ExceptionType = "Access Violation";        break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:  ExceptionType = "Array Bounds Exceeded";   break;
    case EXCEPTION_BREAKPOINT:             ExceptionType = "Breakpoint";              break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:  ExceptionType = "Datatype Misalignment";   break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:     ExceptionType = "Float Divide by Zero";    break;
    case EXCEPTION_FLT_OVERFLOW:           ExceptionType = "Float Overflow";          break;
    case EXCEPTION_FLT_UNDERFLOW:          ExceptionType = "Float Underflow";         break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:    ExceptionType = "Illegal Instruction";     break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:     ExceptionType = "Integer Divide by Zero";  break;
    case EXCEPTION_PRIV_INSTRUCTION:       ExceptionType = "Privileged Instruction";  break;
    case EXCEPTION_STACK_OVERFLOW:         ExceptionType = "Stack Overflow";          break;
    default:                               ExceptionType = "Unknown Exception";       break;
    }

    std::string Info;
    Info.reserve(8192);
    char Buf[1024];

    snprintf(Buf, sizeof(Buf), "Exception Code:    0x%08X\n", ExcRecord->ExceptionCode);
    Info += Buf;
    snprintf(Buf, sizeof(Buf), "Exception Address: 0x%p\n", ExcRecord->ExceptionAddress);
    Info += Buf;
    snprintf(Buf, sizeof(Buf), "Exception Type:    %s\n", ExceptionType);
    Info += Buf;

    if (ExcRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && ExcRecord->NumberParameters >= 2)
    {
        const char* AccessType = ExcRecord->ExceptionInformation[0] ? "write" : "read";
        snprintf(Buf, sizeof(Buf), "AV Type:           %s\n", AccessType);
        Info += Buf;
        snprintf(Buf, sizeof(Buf), "AV Address:        0x%p\n", reinterpret_cast<void*>(ExcRecord->ExceptionInformation[1]));
        Info += Buf;
    }

    {
        HANDLE Process = GetCurrentProcess();
        SymInitialize(Process, nullptr, TRUE);

        HMODULE RipModule = nullptr;
        GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCSTR>(Context->Rip), &RipModule);

        char RipModuleName[MAX_PATH] = {};
        GetModuleFileNameA(RipModule, RipModuleName, MAX_PATH);
        snprintf(Buf, sizeof(Buf), "RIP Module:        %s\n", RipModuleName[0] ? RipModuleName : "Unknown");
        Info += Buf;

        if (RipModule)
        {
            MODULEINFO RipModInfo = {};
            GetModuleInformation(Process, RipModule, &RipModInfo, sizeof(RipModInfo));
            snprintf(Buf, sizeof(Buf), "RIP Offset:        0x%llX\n",
                Context->Rip - reinterpret_cast<uintptr_t>(RipModInfo.lpBaseOfDll));
            Info += Buf;
        }

        char SymBuf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = {};
        PSYMBOL_INFO Symbol = reinterpret_cast<PSYMBOL_INFO>(SymBuf);
        Symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        Symbol->MaxNameLen = MAX_SYM_NAME;
        DWORD64 SymDisp = 0;
        if (SymFromAddr(Process, Context->Rip, &SymDisp, Symbol))
        {
            snprintf(Buf, sizeof(Buf), "RIP Symbol:        %s+0x%llX\n", Symbol->Name, SymDisp);
            Info += Buf;
        }

        IMAGEHLP_LINE64 Line = {};
        DWORD LineDisp = 0;
        Line.SizeOfStruct = sizeof(Line);
        if (SymGetLineFromAddr64(Process, Context->Rip, &LineDisp, &Line))
        {
            snprintf(Buf, sizeof(Buf), "RIP Source:        %s:%lu\n", Line.FileName, Line.LineNumber);
            Info += Buf;
        }
    }

    Info += "\n--- Registers ---\n";
    snprintf(Buf, sizeof(Buf),
        "RAX: %016llX  RBX: %016llX\n"
        "RCX: %016llX  RDX: %016llX\n"
        "RSI: %016llX  RDI: %016llX\n"
        "RSP: %016llX  RBP: %016llX\n"
        "R8:  %016llX  R9:  %016llX\n"
        "R10: %016llX  R11: %016llX\n"
        "R12: %016llX  R13: %016llX\n"
        "R14: %016llX  R15: %016llX\n"
        "RIP: %016llX\n"
        "EFL: %08X\n",
        Context->Rax, Context->Rbx,
        Context->Rcx, Context->Rdx,
        Context->Rsi, Context->Rdi,
        Context->Rsp, Context->Rbp,
        Context->R8, Context->R9,
        Context->R10, Context->R11,
        Context->R12, Context->R13,
        Context->R14, Context->R15,
        Context->Rip,
        Context->EFlags
    );
    Info += Buf;

    {
        HANDLE Process = GetCurrentProcess();
        STACKFRAME64 StackFrame = {};
        StackFrame.AddrPC.Offset = Context->Rip;
        StackFrame.AddrPC.Mode = AddrModeFlat;
        StackFrame.AddrFrame.Offset = Context->Rbp;
        StackFrame.AddrFrame.Mode = AddrModeFlat;
        StackFrame.AddrStack.Offset = Context->Rsp;
        StackFrame.AddrStack.Mode = AddrModeFlat;

        Info += "\n--- Call Stack ---\n";

        CONTEXT CtxCopy = *Context;
        int FrameIndex = 0;
        while (StackWalk64(IMAGE_FILE_MACHINE_AMD64, Process, GetCurrentThread(),
            &StackFrame, &CtxCopy, nullptr,
            SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
        {
            if (StackFrame.AddrPC.Offset == 0) break;

            void* Addr = reinterpret_cast<void*>(StackFrame.AddrPC.Offset);

            char SymBuf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = {};
            PSYMBOL_INFO Symbol = reinterpret_cast<PSYMBOL_INFO>(SymBuf);
            Symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            Symbol->MaxNameLen = MAX_SYM_NAME;
            DWORD64 SymDisp = 0;
            const char* FuncName = "Unknown";
            if (SymFromAddr(Process, reinterpret_cast<DWORD64>(Addr), &SymDisp, Symbol))
                FuncName = Symbol->Name;

            char ModName[MAX_PATH] = {};
            HMODULE FrameMod = nullptr;
            GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(Addr), &FrameMod);
            GetModuleFileNameA(FrameMod, ModName, MAX_PATH);

            DWORD64 ModOffset = 0;
            if (FrameMod)
            {
                MODULEINFO FrameModInfo = {};
                GetModuleInformation(Process, FrameMod, &FrameModInfo, sizeof(FrameModInfo));
                ModOffset = reinterpret_cast<DWORD64>(Addr) - reinterpret_cast<uintptr_t>(FrameModInfo.lpBaseOfDll);
            }

            snprintf(Buf, sizeof(Buf), "#%-2d 0x%p  %s+0x%llX  [%s+0x%llX]\n",
                FrameIndex++, Addr, FuncName, SymDisp,
                ModName[0] ? ModName : "Unknown", ModOffset);
            Info += Buf;

            IMAGEHLP_LINE64 Line = {};
            DWORD LineDisp = 0;
            Line.SizeOfStruct = sizeof(Line);
            if (SymGetLineFromAddr64(Process, reinterpret_cast<DWORD64>(Addr), &LineDisp, &Line))
            {
                snprintf(Buf, sizeof(Buf), "     %s:%lu\n", Line.FileName, Line.LineNumber);
                Info += Buf;
            }
        }
    }

    MessageBoxA(nullptr, Info.c_str(), "Roblox Crashed", MB_OK | MB_ICONERROR);
    return EXCEPTION_CONTINUE_SEARCH;
}
void MainThread(HMODULE hModule)
{
    MessageBoxA(nullptr, "s", "s", S_OK);
    //char appdata[MAX_PATH];
    //SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata);

    //std::filesystem::path yubxdata = std::filesystem::path(appdata) / "yubx";
    //std::filesystem::path Workspace = yubxdata / "workspace";

    //if (!std::filesystem::exists(yubxdata))
    //    std::filesystem::create_directory(yubxdata);

    //if (!std::filesystem::exists(Workspace))
    //    std::filesystem::create_directory(Workspace);

    //Globals::workspace_folder = Workspace;
    //Globals::g_workspaceBase = std::filesystem::absolute(Workspace).lexically_normal();

    //Globals::AppDataInfo = *reinterpret_cast<uintptr_t*>(Offsets::AppdataInfo);
    //Globals::TaskScheduler = *reinterpret_cast<std::uintptr_t*>(Offsets::RawScheduler);
    //Globals::OpCodeLookUp =  reinterpret_cast<BYTE*>(Offsets::OpcodeLookupTable);
    //Globals::RobloxWindow = FindWindowA(NULL, "Roblox");

    //RBX::Renderer->initialize();
    //Communication::Initialize();
    //TaskScheduler::Scheduler->Initialize();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
     /*   AddVectoredContinueHandler(1, ExceptionFilter);
        AddVectoredExceptionHandler(1, ExceptionFilter);
        SetUnhandledExceptionFilter(ExceptionFilter);*/

        std::thread(MainThread, hModule).detach();
    }
    return TRUE;
}

extern "C" __declspec(dllexport) int NextHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}