// c++ remove niger.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<libmem/libmem.h>
#include<tchar.h>

#pragma comment(lib,"libmem.lib")
lm_bool_t
EnumModulesCallback(lm_module_t* pmod,
	lm_void_t* arg)
{
	if (strcmp(pmod->name, "CLibrary.dll") == 0) {
		printf("[*] Module Base: %p\n", (void*)pmod->base);
		printf("[*] Module End:  %p\n", (void*)pmod->end);
		printf("[*] Module Size: %p\n", (void*)pmod->size);
		printf("[*] Module Name: %s\n", pmod->name);
		printf("[*] Module Path: %s\n", pmod->path);
		printf("====================\n");
		lm_address_t ptr;
		ptr = pmod->base;
		ptr = ptr + 0x395f68;
		printf("开始写入\n");
		
			
		int val = 256;
		if (LM_WriteMemoryEx((lm_process_t*)arg, ptr, (unsigned char*)&val, 4)) {
			printf("写入成功\n");
		}
			
		
	}
	return LM_TRUE;

	
}
lm_bool_t
EnumProcessesCallback(lm_process_t* pproc,
	lm_void_t* arg)
{
	if (strcmp(pproc->name, "GenshinImpact.exe") == 0) {
		printf("[*] Process PID:  %u\n", pproc->pid);
		printf("[*] Process PPID: %u\n", pproc->ppid);
		printf("[*] Process Name: %s\n", pproc->name);
		printf("[*] Process Path: %s\n", pproc->path);
		printf("[*] Process Bits: %zu\n", pproc->bits);
		printf("====================\n");
		LM_EnumModulesEx(pproc,EnumModulesCallback, pproc);
		
	}
	return LM_TRUE;

	
}

int
main()
{
	printf("开始去除图片\n");
	lm_process_t proc;
	int time = 0;
	while(!LM_FindProcess((lm_string_t)"GenshinImpact.exe", &proc)) {
		
		printf("无法找到genshin\n");
		if (time > 10) break;
		time++;
		Sleep(1000);
	}
	lm_process_t* pproc = &proc;
	printf("[*] Process PID:  %u\n", pproc->pid);
	printf("[*] Process PPID: %u\n", pproc->ppid);
	printf("[*] Process Name: %s\n", pproc->name);
	printf("[*] Process Path: %s\n", pproc->path);
	printf("[*] Process Bits: %zu\n", pproc->bits);
	printf("====================\n");
	lm_module_t module;
	lm_module_t* pmod = &module;
	while(!LM_FindModuleEx(pproc, (lm_string_t)"CLibrary.dll", pmod)) {
		printf("无法找到CLibrary\n");
		if (time > 20) break;
		time++;
		Sleep(1000);
	}
	lm_address_t ptr = pmod->base+0x395f68;
	printf("[*] Module Base: %p\n", (void*)pmod->base);
	printf("[*] Module End:  %p\n", (void*)pmod->end);
	printf("[*] Module Size: %p\n", (void*)pmod->size);
	printf("[*] Module Name: %s\n", pmod->name);
	printf("[*] Module Path: %s\n", pmod->path);
	printf("====================\n");
	int value = 256;
	if (!LM_WriteMemoryEx(pproc, (lm_address_t)ptr, (lm_bytearr_t)&value, 4)) {
		printf("写入失败\n");
	}

}

//int main()
//{	
//	
//	std::cout << "开始寻找进程\n" << std::endl;
//	lm_process_t genshin;
//	
//	while (!LM_FindProcess(const_cast<char*>("GenshinImpact.exe"), &genshin)) {
//		Sleep(1000);
//	}
//	if (!LM_FindProcess(const_cast<char*>("GenshinImpact.exe"), &genshin)) {
//		printf("%ls", genshin.name);
//		printf("未找到进程\n");
//		return 0;
//	}
//	lm_module_t module;
//	while (!LM_FindModuleEx(&genshin,(char*)"CLibrary.dll",&module))
//	{
//		Sleep(1000);
//	}
//	LM_FindModuleEx(&genshin, (char*)"CLibrary.dll", &module);
//	printf("module name %s\n", module.name);
//	lm_address_t ptr;
//	ptr = module.base;
//	ptr = ptr + 0x395f68;
//	printf("开始写入\n");
//
//	try
//	{
//		int val = 256;
//		if (LM_WriteMemoryEx(&genshin, ptr, (unsigned char*)&val, 4)) {
//			printf("写入成功\n");
//		}
//	}
//	catch (const std::exception&)
//	{
//
//	}
//
//	return 0;
//	
//	
//}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
