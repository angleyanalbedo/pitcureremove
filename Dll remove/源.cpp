
#include"pch.h"
bool tcscmp(PTCHAR str0, PTCHAR str2) {
#ifdef UNICODE 
    return _wcsicmp(str0, str2);
#else
    retun strcmp(str0, str1);
#endif 
}
PBYTE GetProcessModuleBase(DWORD pid, CONST TCHAR * moduleName) {	// 根据 PID 、模块名（需要写后缀，如：".dll"），获取模块入口地址。
    MODULEENTRY32 moduleEntry;
    HANDLE handle = NULL;
    handle = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid); //  获取进程快照中包含在th32ProcessID中指定的进程的所有的模块。
    if (!handle) {
        CloseHandle(handle);
        return NULL;
    }
    ZeroMemory(&moduleEntry, sizeof(MODULEENTRY32));
    moduleEntry.dwSize = sizeof(MODULEENTRY32);
    if (!Module32First(handle, &moduleEntry)) {
        CloseHandle(handle);
        return NULL;
    }
    do {
        if (tcscmp(moduleEntry.szModule, (PTCHAR)moduleName) == 0) {

            return moduleEntry.modBaseAddr;
        }
    } while (Module32Next(handle, &moduleEntry));
    CloseHandle(handle);
    return 0;
}


int Run() {
    
    PBYTE base = nullptr;
    int i = 0;
    while (!(base = GetProcessModuleBase(0, TEXT("CLibrary.dll"))))
    {
        i++;
        Sleep(1000);
        if (i > 20) {
            printf("超时\n");
        }
    }
    PBYTE ptr = base + 0x395F68;
    try
    {
        int value = 256;
        DWORD oldProtect;
        VirtualProtect(ptr, sizeof(int), PAGE_WRITECOPY, &oldProtect);
        memcpy(ptr, &value, sizeof(int));
        VirtualProtect(ptr, sizeof(int), oldProtect, &oldProtect);
    }
    catch (const std::exception&)
    {
        
    }
   
    return 0;
}