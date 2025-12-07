#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

DWORD GetProcessId(const wchar_t* procname);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);