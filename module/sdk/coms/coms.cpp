#include "sdk/update/external.hpp"
#include "sdk/update/classes.hpp"
#include "sdk/update/offsets.hpp"
#include "sdk/update/fflags.hpp"
#include "sdk/update/cfg.hpp"
//
#include "sdk/scheduler/scheduler.h"
//
#include "coms.h"
//
#include "windows.h"
#include <string>

static bool read(HANDLE hPipe, void* Buffer, DWORD Size)
{
    DWORD TotalRead = 0;
    while (TotalRead < Size)
    {
        DWORD CurrentChink = 0;
        if (!ReadFile(hPipe, static_cast<char*>(Buffer) + TotalRead, Size - TotalRead, &CurrentChink, nullptr) || CurrentChink == 0)
            return false;

        TotalRead += CurrentChink;
    }
    return true;
}

void host()
{
    while (true)
    {
        HANDLE hPipe = CreateNamedPipeW((L"\\\\.\\pipe\\" + std::wstring(L"shittyserver")).c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, (8 * 1024 * 1024), (8 * 1024 * 1024), 5000, nullptr);
        if (hPipe == INVALID_HANDLE_VALUE)
        {
            Sleep(100);
            continue;
        }

        BOOL Connection = ConnectNamedPipe(hPipe, nullptr) || GetLastError() == ERROR_PIPE_CONNECTED;
        if (!Connection)
        {
            CloseHandle(hPipe);
            continue;
        }

        uint32_t script_buf = 0;
        if (!read(hPipe, &script_buf, sizeof(script_buf)) || script_buf == 0 || script_buf > (8 * 1024 * 1024))
        {
            CloseHandle(hPipe);
            continue;
        }

        std::vector<char> Buffer(script_buf);
        if (!read(hPipe, Buffer.data(), script_buf))
        {
            CloseHandle(hPipe);
            continue;
        }

        std::string Script(Buffer.data(), script_buf);
        taskscheduler->execute(Script);

        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);
    }
}

void communication_t::setup()
{
    std::thread(host).detach();
}
