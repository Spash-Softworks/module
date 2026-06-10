// version-ad5d3e2906444472

#define MODULE_NAME "rat.dll"

#pragma warning(disable: 4996)

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

#pragma comment(lib, "Psapi.lib")

//update
static const uint64_t patcheb[] = {
    0x740fda,  0x77ddf4,  0x79cb63,  0x8bd962,  0x8f3225,
    0x7ba9cf,  0x7a90a2,  0x82fbd7,  0x81c512,  0x7b0163,
    0x719bd2,  0x740f68,  0x784b38,  0x11cf19f, 0x11a8182,
    0x11bd880, 0x12f14aa,
};
static const uint64_t patchnope[] = {
    0x785ec4, 0x787ef3, 0x78997c, 0x79b661, 0x79d5ea,
    0x7aef5f, 0x7e52b2, 0x806dc4, 0x828de3, 0x909d04,
    0x7a8ee0, 0x799cc8, 0x8eaf51,
};




typedef LONG NTSTATUS;
#define NT_SUCCESS(s) ((NTSTATUS)(s) >= 0)

typedef NTSTATUS(NTAPI* FnNtUnmapViewOfSection)(HANDLE, PVOID);
typedef NTSTATUS(NTAPI* FnNtQueryInformationProcess)(HANDLE, ULONG, PVOID, ULONG, PULONG);
typedef NTSTATUS(NTAPI* FnNtQueryObject)(HANDLE, ULONG, PVOID, ULONG, PULONG);
typedef NTSTATUS(NTAPI* FnNtSetIoCompletion)(HANDLE, ULONG_PTR, PVOID, NTSTATUS, ULONG_PTR);

static FnNtUnmapViewOfSection      pNtUnmapViewOfSection;
static FnNtQueryInformationProcess pNtQueryInformationProcess;
static FnNtQueryObject             pNtQueryObject;
static FnNtSetIoCompletion         pNtSetIoCompletion;

static const uint64_t kPatchRET[]    = { 0x130cf10 };
static const uint64_t kPatchJMPRAX[] = { 0xf9bce0 };

static bool init() {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) return false;
    pNtUnmapViewOfSection      = (FnNtUnmapViewOfSection)     GetProcAddress(ntdll, "NtUnmapViewOfSection");
    pNtQueryInformationProcess = (FnNtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");
    pNtQueryObject             = (FnNtQueryObject)            GetProcAddress(ntdll, "NtQueryObject");
    pNtSetIoCompletion         = (FnNtSetIoCompletion)        GetProcAddress(ntdll, "NtSetIoCompletion");
    return pNtUnmapViewOfSection && pNtQueryInformationProcess &&
           pNtQueryObject && pNtSetIoCompletion;
}

static bool write(HANDLE hp, LPVOID target, const void* data, SIZE_T size) {
    DWORD old = 0;
    if (!VirtualProtectEx(hp, target, size, PAGE_EXECUTE_READWRITE, &old)) return false;
    WriteProcessMemory(hp, target, data, size, nullptr);
    VirtualProtectEx(hp, target, size, old, &old);
    return true;
}

static void patch(HANDLE hp, LPCVOID base, uint64_t rva, const void* bytes, SIZE_T sz) {
    write(hp, (LPBYTE)base + rva, bytes, sz);
}

static HMODULE module(HANDLE hp, const char* name) {
    HMODULE mods[1024] = {};
    DWORD needed = 0;
    if (!K32EnumProcessModulesEx(hp, mods, sizeof(mods), &needed, LIST_MODULES_ALL)) return nullptr;
    char buf[MAX_PATH];
    for (DWORD i = 0; i < needed / sizeof(HMODULE); i++) {
        if (!K32GetModuleBaseNameA(hp, mods[i], buf, sizeof(buf))) continue;
        if (_stricmp(buf, name) == 0) return mods[i];
    }
    return nullptr;
}

static bool loaded(HANDLE hp, const char* name) {
    return module(hp, name) != nullptr;
}

struct SectionInfo { LPVOID va; SIZE_T size; };

static SectionInfo section(HANDLE hp, LPCVOID base, const char* name) {
    SectionInfo r = {};
    uint8_t hdr[0x1000] = {};
    SIZE_T rd = 0;
    if (!ReadProcessMemory(hp, base, hdr, sizeof(hdr), &rd) || rd < 0x40) return r;
    auto* dos = (IMAGE_DOS_HEADER*)hdr;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return r;
    auto* nt = (IMAGE_NT_HEADERS64*)(hdr + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return r;
    auto* sec = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++) {
        if (strncmp((char*)sec->Name, name, 8) == 0) {
            r.va   = (LPBYTE)base + sec->VirtualAddress;
            r.size = sec->Misc.VirtualSize;
            return r;
        }
    }
    return r;
}

static bool remap(HANDLE hp, LPCVOID base) {
    SectionInfo sec = section(hp, base, ".byfron");
    if (!sec.va || !sec.size) return false;
    std::vector<uint8_t> buf(sec.size);
    SIZE_T rd = 0;
    ReadProcessMemory(hp, sec.va, buf.data(), sec.size, &rd);
    if (!NT_SUCCESS(pNtUnmapViewOfSection(hp, sec.va))) return false;
    LPVOID nv = VirtualAllocEx(hp, sec.va, sec.size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!nv) return false;
    WriteProcessMemory(hp, nv, buf.data(), buf.size(), nullptr);
    DWORD old = 0;
    VirtualProtectEx(hp, nv, sec.size, PAGE_EXECUTE_READ, &old);
    return true;
}

static void threads(DWORD pid, bool suspend) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snap == INVALID_HANDLE_VALUE) return;
    THREADENTRY32 te = {};
    te.dwSize = sizeof(te);
    if (Thread32First(snap, &te)) {
        do {
            if (te.th32OwnerProcessID == pid) {
                HANDLE ht = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (ht) {
                    if (suspend) SuspendThread(ht);
                    else         ResumeThread(ht);
                    CloseHandle(ht);
                }
            }
        } while (Thread32Next(snap, &te));
    }
    CloseHandle(snap);
}

static FARPROC get_export(HANDLE hp, LPCVOID base, const char* fn) {
    uint8_t hdr[0x200] = {};
    SIZE_T rd = 0;
    ReadProcessMemory(hp, base, hdr, sizeof(hdr), &rd);
    if (rd < 0x40) return nullptr;
    auto* dos = (IMAGE_DOS_HEADER*)hdr;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return nullptr;
    uint8_t nt_buf[sizeof(IMAGE_NT_HEADERS64)] = {};
    ReadProcessMemory(hp, (LPBYTE)base + dos->e_lfanew, nt_buf, sizeof(nt_buf), &rd);
    auto* nt = (IMAGE_NT_HEADERS64*)nt_buf;
    if (nt->Signature != IMAGE_NT_SIGNATURE) return nullptr;
    auto& ed = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (!ed.VirtualAddress) return nullptr;
    uint8_t exp_buf[sizeof(IMAGE_EXPORT_DIRECTORY)] = {};
    ReadProcessMemory(hp, (LPBYTE)base + ed.VirtualAddress, exp_buf, sizeof(exp_buf), &rd);
    auto* exp = (IMAGE_EXPORT_DIRECTORY*)exp_buf;
    DWORD n = exp->NumberOfNames;
    std::vector<DWORD> names(n), funcs(exp->NumberOfFunctions);
    std::vector<WORD>  ords(n);
    ReadProcessMemory(hp, (LPBYTE)base + exp->AddressOfNames,        names.data(), n * 4,                      &rd);
    ReadProcessMemory(hp, (LPBYTE)base + exp->AddressOfNameOrdinals, ords.data(),  n * 2,                      &rd);
    ReadProcessMemory(hp, (LPBYTE)base + exp->AddressOfFunctions,    funcs.data(), exp->NumberOfFunctions * 4, &rd);
    size_t flen = strlen(fn);
    char nbuf[256] = {};
    for (DWORD i = 0; i < n; i++) {
        ReadProcessMemory(hp, (LPBYTE)base + names[i], nbuf, flen + 1, &rd);
        if (strcmp(nbuf, fn) == 0) return (FARPROC)((LPBYTE)base + funcs[ords[i]]);
    }
    return nullptr;
}

static bool iocp(HANDLE hp, LPVOID sc_remote) {
    SIZE_T bufsz = 0x20000;
    std::vector<uint64_t> htbl;
    NTSTATUS st;
    while (true) {
        htbl.resize(bufsz / 8);
        st = pNtQueryInformationProcess(hp, 0x33, htbl.data(), (ULONG)bufsz, nullptr);
        if (st != (NTSTATUS)0xC0000004) break;
        bufsz *= 2;
    }
    if (!NT_SUCCESS(st) || htbl[0] == 0) return false;

    uint64_t count = htbl[0];
    std::vector<uint8_t> obj(0x4000);
    HANDLE iocp = nullptr;

    for (uint64_t i = 0; i < count && !iocp; i++) {
        HANDLE rh = (HANDLE)htbl[i * 5 + 2];
        HANDLE lh = nullptr;
        if (!DuplicateHandle(hp, rh, GetCurrentProcess(), &lh, 0, FALSE, DUPLICATE_SAME_ACCESS)) continue;
        memset(obj.data(), 0, obj.size());
        st = pNtQueryObject(lh, 2, obj.data(), (ULONG)obj.size(), nullptr);
        if (NT_SUCCESS(st)) {
            uint64_t np = *(uint64_t*)(obj.data() + 8);
            if (np) {
                wchar_t tn[32] = {};
                memcpy(tn, (void*)np, sizeof(tn));
                if (wcscmp(tn, L"IoCompletion") == 0) { iocp = lh; break; }
            }
        }
        CloseHandle(lh);
    }

    if (!iocp) return false;

    LPVOID slot = nullptr;
    LPVOID scan = (LPVOID)0x10000;
    MEMORY_BASIC_INFORMATION mbi = {};
    uint8_t pg[0x1000];
    SIZE_T rd = 0;

    while (VirtualQueryEx(hp, scan, &mbi, sizeof(mbi)) == sizeof(mbi)) {
        LPVOID next = (LPBYTE)mbi.BaseAddress + mbi.RegionSize;
        if (mbi.State == MEM_COMMIT &&
            (mbi.Protect & PAGE_READWRITE) &&
            !(mbi.Protect & PAGE_NOACCESS) &&
            !(mbi.Protect & PAGE_GUARD) &&
            mbi.RegionSize > 0x47) {
            SIZE_T off = 0;
            while (off < mbi.RegionSize && !slot) {
                SIZE_T chunk = std::min((SIZE_T)sizeof(pg), mbi.RegionSize - off);
                if (!ReadProcessMemory(hp, (LPBYTE)mbi.BaseAddress + off, pg, chunk, &rd)) break;
                for (SIZE_T j = 0; j + 0x48 <= rd; j++) {
                    SIZE_T z = 0;
                    while (z < 0x48 && pg[j + z] == 0) z++;
                    if (z >= 0x48) { slot = (LPBYTE)mbi.BaseAddress + off + j; break; }
                }
                off += chunk;
            }
        }
        if (slot) break;
        if (next <= scan) break;
        scan = next;
    }

    if (!slot) { CloseHandle(iocp); return false; }

    struct { uint64_t pad[7]; uint64_t cb; uint64_t tail; } d = {};
    d.cb = (uint64_t)sc_remote;
    WriteProcessMemory(hp, slot, &d, sizeof(d), nullptr);

    NTSTATUS rc = pNtSetIoCompletion(iocp, (ULONG_PTR)slot, nullptr, 0, 0);
    CloseHandle(iocp);
    return NT_SUCCESS(rc);
}

static std::vector<uint8_t> shellcode(FARPROC loadlib, LPVOID path) {
    static const uint8_t kTpl[] = { // loadlib shellcode
        0x48, 0xB9, 0,0,0,0,0,0,0,0,
        0x48, 0xB8, 0,0,0,0,0,0,0,0,
        0x48, 0x83, 0xEC, 0x28,
        0xFF, 0xD0,
        0x48, 0x83, 0xC4, 0x28,
        0xC3,
    };
    std::vector<uint8_t> sc(kTpl, kTpl + sizeof(kTpl));
    uint64_t pv = (uint64_t)path, lv = (uint64_t)loadlib;
    memcpy(sc.data() + 2,  &pv, 8);
    memcpy(sc.data() + 12, &lv, 8);
    return sc;
}

static bool inject(const char* dll, HANDLE hp) {
    char cwd[MAX_PATH] = {};
    GetCurrentDirectoryA(sizeof(cwd), cwd);
    std::string path = std::string(cwd) + "\\" + dll;

    HMODULE k32 = module(hp, "KERNEL32.DLL");
    if (!k32) k32 = module(hp, "kernel32.dll");
    HMODULE kb  = module(hp, "KERNELBASE.dll");
    FARPROC ll  = nullptr;
    if (k32) ll = get_export(hp, k32, "LoadLibraryA");
    if (!ll && kb) ll = get_export(hp, kb, "LoadLibraryA");
    if (!ll) ll = (FARPROC)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (!ll) return false;

    LPVOID pbuf = VirtualAllocEx(hp, nullptr, 0x108, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!pbuf) return false;
    WriteProcessMemory(hp, pbuf, path.c_str(), path.size() + 1, nullptr);

    auto sc = shellcode(ll, pbuf);
    LPVOID sb = VirtualAllocEx(hp, nullptr, sc.size(), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!sb) return false;
    WriteProcessMemory(hp, sb, sc.data(), sc.size(), nullptr);

    if (!iocp(hp, sb)) return false;

    while (!loaded(hp, dll))
        Sleep(1);

    return true;
}

static const uint8_t nthooktemplate[0x40] = {
    /* 00 */ 0x41,0x52,                              // push r10
    /* 02 */ 0x41,0x53,                              // push r11
    /* 04 */ 0x4D,0x85,0xC9,                         // test r9, r9
    /* 07 */ 0x74,0x1B,                              // jz > 0x24 (passthrough)
    /* 09 */ 0x4D,0x8B,0x11,                         // mov r10, [r9]  ; UniqueProcess
    /* 0C */ 0x44,0x8B,0x1D, 0x25,0x00,0x00,0x00,    // mov r11d, [rip+0x25] > 0x38
    /* 13 */ 0x45,0x3B,0xD3,                         // cmp r10d, r11d
    /* 16 */ 0x75,0x0C,                              // jne > 0x24 (passthrough)
    /* 18 */ 0x41,0x5B,                              // pop r11
    /* 1A */ 0x41,0x5A,                              // pop r10
    /* 1C */ 0xB8,0x22,0x00,0x00,0xC0,               // mov eax, STATUS_ACCESS_DENIED
    /* 21 */ 0xC3,                                   // ret
    /* 22 */ 0x00,0x00,                              // padding
    /* 24 */ 0x41,0x5B,                              // pop r11
    /* 26 */ 0x41,0x5A,                              // pop r10
    /* 28 */ 0x4C,0x8B,0xD1,                         // mov r10, rcx  (NT abi)
    /* 2B */ 0x8B,0x05, 0x03,0x00,0x00,0x00,         // mov eax, [rip+3] > 0x34
    /* 31 */ 0x0F,0x05,                              // syscall
    /* 33 */ 0xC3,                                   // ret
    /* 34 */ 0x00,0x00,0x00,0x00,                    // syscall_number DWORD
    /* 38 */ 0x00,0x00,0x00,0x00,                    // roblox_pid DWORD
    /* 3C */ 0x00,0x00,0x00,0x00,                    // padding
};

static LPVOID alloc_near(HANDLE hp, LPVOID target, SIZE_T size) {
    SYSTEM_INFO si = {};
    GetSystemInfo(&si);
    SIZE_T gran = si.dwAllocationGranularity;
    ULONG_PTR base = (ULONG_PTR)target;
    ULONG_PTR lo = base > 0x70000000 ? base - 0x70000000 : (ULONG_PTR)si.lpMinimumApplicationAddress;
    ULONG_PTR hi = base + 0x70000000;
    if (hi > (ULONG_PTR)si.lpMaximumApplicationAddress) hi = (ULONG_PTR)si.lpMaximumApplicationAddress;
    lo = (lo + gran - 1) & ~(ULONG_PTR)(gran - 1);
    MEMORY_BASIC_INFORMATION mbi;
    for (ULONG_PTR at = (base & ~(ULONG_PTR)(gran - 1)); at >= lo && at <= base; at -= gran) {
        if (VirtualQueryEx(hp, (LPVOID)at, &mbi, sizeof(mbi)) != sizeof(mbi)) break;
        if (mbi.State == MEM_FREE) {
            ULONG_PTR aligned = ((ULONG_PTR)mbi.BaseAddress + gran - 1) & ~(ULONG_PTR)(gran - 1);
            if (aligned + size <= (ULONG_PTR)mbi.BaseAddress + mbi.RegionSize) {
                LPVOID p = VirtualAllocEx(hp, (LPVOID)aligned, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
                if (p) return p;
            }
        }
        if (at < gran) break;
    }
    for (ULONG_PTR scan = base; scan < hi;) {
        if (VirtualQueryEx(hp, (LPVOID)scan, &mbi, sizeof(mbi)) != sizeof(mbi)) break;
        if (mbi.State == MEM_FREE) {
            ULONG_PTR aligned = ((ULONG_PTR)mbi.BaseAddress + gran - 1) & ~(ULONG_PTR)(gran - 1);
            if (aligned + size <= (ULONG_PTR)mbi.BaseAddress + mbi.RegionSize) {
                LPVOID p = VirtualAllocEx(hp, (LPVOID)aligned, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
                if (p) return p;
            }
        }
        ULONG_PTR next = (ULONG_PTR)mbi.BaseAddress + mbi.RegionSize;
        if (next <= scan) break;
        scan = next;
    }
    return nullptr;
}

static uint32_t g_nt_sysnum = 0;

static void hook_ntopen(DWORD target_pid, DWORD roblox_pid) {
    HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, target_pid);
    if (!hp) return;

    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    FARPROC nt_open = GetProcAddress(ntdll, "NtOpenProcess");
    if (!nt_open) { CloseHandle(hp); return; }

    LPVOID page = alloc_near(hp, nt_open, 0x1000);
    if (!page)
        page = VirtualAllocEx(hp, nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!page) { CloseHandle(hp); return; }

    uint8_t hook_page[0x40] = {};
    memcpy(hook_page, nthooktemplate, sizeof(hook_page));
    *(uint32_t*)(hook_page + 0x34) = g_nt_sysnum;
    *(uint32_t*)(hook_page + 0x38) = roblox_pid;

    if (!WriteProcessMemory(hp, page, hook_page, sizeof(hook_page), nullptr)) {
        VirtualFreeEx(hp, page, 0, MEM_RELEASE);
        CloseHandle(hp); return;
    }

    DWORD old = 0;
    VirtualProtectEx(hp, page, 0x1000, PAGE_EXECUTE_READ, &old);

    static const char* const kFns[] = { "NtOpenProcess", "ZwOpenProcess" };
    for (const char* fn : kFns) {
        FARPROC fp = GetProcAddress(ntdll, fn);
        if (!fp) continue;
        if (!VirtualProtectEx(hp, fp, 0x10, PAGE_EXECUTE_READWRITE, &old)) continue;
        int64_t diff = (int64_t)page - (int64_t)fp - 5;
        if (diff >= (int64_t)INT32_MIN && diff <= (int64_t)INT32_MAX) {
            uint8_t patch[5] = { 0xE9 };
            *(int32_t*)(patch + 1) = (int32_t)diff;
            WriteProcessMemory(hp, fp, patch, 5, nullptr);
        } else {
            uint8_t patch[14] = { 0xFF, 0x25, 0,0,0,0 };
            *(uint64_t*)(patch + 6) = (uint64_t)page;
            WriteProcessMemory(hp, fp, patch, 14, nullptr);
        }
        VirtualProtectEx(hp, fp, 0x10, old, &old);
    }

    CloseHandle(hp);
}

static void hook_64(DWORD roblox_pid) {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    FARPROC nt_open = ntdll ? GetProcAddress(ntdll, "NtOpenProcess") : nullptr;
    if (nt_open) {
        uint8_t b[8] = {};
        memcpy(b, nt_open, 8);
        if (b[0] == 0x4C && b[1] == 0x8B && b[2] == 0xD1 && b[3] == 0xB8)
            g_nt_sysnum = *(uint32_t*)(b + 4);
    }
    if (!g_nt_sysnum) return;

    DWORD self = GetCurrentProcessId();
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return;
    PROCESSENTRY32W pe = {};
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(snap, &pe)) {
        do {
            DWORD pid = pe.th32ProcessID;
            if (pid == 0 || pid == 4 || pid == roblox_pid || pid == self) continue;
            HANDLE hp = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (!hp) continue;
            BOOL wow = FALSE;
            IsWow64Process(hp, &wow);
            if (!wow) {
                bool skip = false;
                HANDLE tok = nullptr;
                if (OpenProcessToken(hp, TOKEN_QUERY, &tok)) {
                    DWORD elev = 0, needed = 4;
                    if (GetTokenInformation(tok, TokenElevation, &elev, 4, &needed) && elev)
                        skip = true;
                    CloseHandle(tok);
                }
                if (!skip)
                    hook_ntopen(pid, roblox_pid);
            }
            CloseHandle(hp);
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
}

static void patches(HANDLE hp, LPCVOID base) {
    static const uint8_t EB      = 0xEB;
    static const uint8_t nope[6] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
    static const uint8_t ret     = 0xC3;
    static const uint8_t jmp[2]  = { 0xFF, 0xE0 };

    for (auto r : patcheb)    patch(hp, base, r, &EB,  1);
    for (auto r : patchnope)  patch(hp, base, r, nope, 6);
    for (auto r : kPatchRET)   patch(hp, base, r, &ret, 1);
    for (auto r : kPatchJMPRAX)patch(hp, base, r, jmp,  2);
}

int main(int argc, char** argv) {
    if (!init()) return 1;

    DWORD pid = 0;
    if (argc < 2) {
        HWND hw = FindWindowA(nullptr, "Roblox");
        if (hw) { DWORD t = 0; GetWindowThreadProcessId(hw, &t); pid = t; }
        if (!pid) return 1;
    } else {
        pid = (DWORD)strtoul(argv[1], nullptr, 10);
    }

    HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hp) return 1;

    HMODULE base = module(hp, "RobloxPlayerBeta.dll");
    if (!base) { CloseHandle(hp); return 1; }

    hook_64(pid);

    threads(pid, true);
    remap(hp, base);
    patches(hp, base);
    threads(pid, false);

    if (inject(MODULE_NAME, hp))
        printf("injected\n");

    CloseHandle(hp);
    return 0;
}