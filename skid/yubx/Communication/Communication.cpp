#include <Communication/Communication.hpp>
#include <Exploit/TaskScheduler/TaskScheduler.hpp>
#include <Exploit/Globals.hpp>
#include <TlHelp32.h>
#include "cpr/cpr.h"

static bool ReadExactSocket(SOCKET Socket, void* Buffer, size_t Size)
{
    char* Out = static_cast<char*>(Buffer);
    size_t Total = 0;
    while (Total < Size)
    {
        int Received = recv(Socket, Out + Total, static_cast<int>(Size - Total), 0);
        if (Received <= 0)
            return false;
        Total += static_cast<size_t>(Received);
    }
    return true;
}

bool IsProcessRunning(const wchar_t* processName)
{
    PROCESSENTRY32W entry{};
    entry.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    if (Process32FirstW(snapshot, &entry))
    {
        do
        {
            if (_wcsicmp(entry.szExeFile, processName) == 0)
            {
                CloseHandle(snapshot);
                return true;
            }

        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return false;
}

void Communication::SendToConsole(const std::string& message, bool isError)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
        return;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6970);
    inet_pton(AF_INET, ("127.0.0.1"), &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0)
    {
        uint8_t type = isError ? 1 : 0;
        uint32_t len = htonl(static_cast<uint32_t>(message.size()));

        send(sock, (char*)&type, 1, 0);
        send(sock, (char*)&len, 4, 0);
        send(sock, message.c_str(), static_cast<int>(message.size()), 0);
    }

    closesocket(sock);
}


void TcpServer()
{
    WSADATA Wsa;
    if (WSAStartup(MAKEWORD(2, 2), &Wsa) != 0)
        return;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    addrinfo Hints{};
    addrinfo* Result = nullptr;

    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;
    Hints.ai_protocol = IPPROTO_TCP;
    Hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(("127.0.0.1"), ("6969"), &Hints, &Result) != 0)
    {
        WSACleanup();
        return;
    }

    ListenSocket = socket(Result->ai_family, Result->ai_socktype, Result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        freeaddrinfo(Result);
        WSACleanup();
        return;
    }

    BOOL Opt = TRUE;
    setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&Opt), sizeof(Opt));

    if (bind(ListenSocket, Result->ai_addr, static_cast<int>(Result->ai_addrlen)) == SOCKET_ERROR)
    {
        closesocket(ListenSocket);
        freeaddrinfo(Result);
        WSACleanup();
        return;
    }

    freeaddrinfo(Result);

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    while (true)
    {
        ClientSocket = accept(ListenSocket, nullptr, nullptr);
        if (ClientSocket == INVALID_SOCKET)
        {
            Sleep(100);
            continue;
        }

        uint32_t NetLen = 0;
        if (!ReadExactSocket(ClientSocket, &NetLen, sizeof(NetLen)))
        {
            closesocket(ClientSocket);
            continue;
        }

        uint32_t ScriptLen = ntohl(NetLen);
        if (ScriptLen == 0 || ScriptLen > (8 * 1024 * 1024))
        {
            closesocket(ClientSocket);
            continue;
        }

        std::vector<char> Buffer(ScriptLen);
        if (!ReadExactSocket(ClientSocket, Buffer.data(), ScriptLen))
        {
            closesocket(ClientSocket);
            continue;
        }

        std::string Script(Buffer.data(), Buffer.size());
        TaskScheduler::Scheduler->ScheduleScript(Script);

        closesocket(ClientSocket);
    }

    closesocket(ListenSocket);
    WSACleanup();
}

void Communication::Initialize()
{
    std::thread(TcpServer).detach();
}