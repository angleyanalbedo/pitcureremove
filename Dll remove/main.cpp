#include"pch.h"
#pragma comment(lib,"libmem.lib")
lm_bool_t
EnumModulesCallback(lm_module_t* pmod,
	lm_void_t* arg)
{
	
	if (pmod->path == L"CLibrary.dll") {
		printf("[*] Module Base: %p\n", (void*)pmod->base);
		printf("[*] Module End:  %p\n", (void*)pmod->end);
		printf("[*] Module Size: %p\n", (void*)pmod->size);
		printf("[*] Module Name: %s\n", pmod->name);
		printf("[*] Module Path: %s\n", pmod->path);
		printf("====================\n");
		lm_address_t base = pmod->base;
		lm_address_t ptr = base + 0x395f68;
		int value = 256;
		LM_WriteMemory(ptr, (lm_byte_t*) & value, sizeof(int));
		printf("[*] ÊýÖµÊÇ%d", value);
		
	}

	return LM_TRUE;
}

int Run() {
	if (!LM_EnumModules(EnumModulesCallback, LM_NULL)) {
		return 0;
	}
	
	
	

	return 0;
}