#include <iostream>
#include <Windows.h>
#include <vector>
#include "process.h"

int main() {
	DWORD procId = GetProcessId(L"ac_client.exe");

	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	std::cout << "Process ID: " << procId << std::endl;
	std::cout << "Module Base Address: 0x" << std::hex << moduleBase << std::dec << std::endl;

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	uintptr_t dynamicPtrAdress = moduleBase + 0x17E0A8;

	std::cout << "dynamicPtrAdress: 0x" << std::hex << dynamicPtrAdress << std::dec << std::endl;

	std::vector<unsigned int> hpOffsets = { 0xEC };
	uintptr_t hpAddress = FindDMAAddy(hProcess, dynamicPtrAdress, hpOffsets);

	std::cout << "HP Address: 0x" << std::hex << hpAddress << std::endl;

	int hpValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)hpAddress, &hpValue, sizeof(hpValue), nullptr);

	std::cout << "HP Value: " << std::dec << hpValue << std::endl;

	int newHpValue = 9999999;

	while (true) {
		WriteProcessMemory(hProcess, (BYTE*)hpAddress, &newHpValue, sizeof(newHpValue), nullptr);
	}
}
