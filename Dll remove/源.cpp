
#include"pch.h"
bool tcscmp(PTCHAR str0, PTCHAR str2) {
#ifdef UNICODE 
    return _wcsicmp(str0, str2);
#else
    retun strcmp(str0, str1);
#endif 
}
PBYTE GetProcessModuleBase(DWORD pid, CONST TCHAR * moduleName) {	// ���� PID ��ģ��������Ҫд��׺���磺".dll"������ȡģ����ڵ�ַ��
    MODULEENTRY32 moduleEntry;
    HANDLE handle = NULL;
    handle = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid); //  ��ȡ���̿����а�����th32ProcessID��ָ���Ľ��̵����е�ģ�顣
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
            printf("��ʱ\n");
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