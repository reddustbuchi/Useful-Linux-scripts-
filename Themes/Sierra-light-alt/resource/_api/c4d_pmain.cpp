// this is the "glue" to C4D...
// please modify only if you know exactly what you are doing...

#ifdef __PC
	#include "windows_include.h"
#endif

#include "c4d_plugin.h"
#include "c4d_file.h"
#include "c4d_resource.h"

#ifdef __MAC
	#ifdef __cplusplus
	extern "C" {
	#endif

	#define C4D_MAIN Int32 __attribute__((visibility("default"))) c4d_main(Int32 action, void* p1, void* p2, void* p3)
	C4D_MAIN;

	#ifdef __cplusplus
	}
	#endif
#elif defined __PC
	HINSTANCE g_hinstDLL;
	LPVOID g_lpReserved;

	#ifdef __cplusplus
	extern "C" {
	#endif

	#define C4D_MAIN Int32 __declspec(dllexport) c4d_main(Int32 action, void* p1, void* p2, void* p3)
	C4D_MAIN;

	#ifndef __WINCRTINIT
	BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
				g_hinstDLL = (HINSTANCE)hModule;
				g_lpReserved = lpReserved;
			//case DLL_THREAD_ATTACH:
			//case DLL_THREAD_DETACH:
			//case DLL_PROCESS_DETACH:
				break;
		}
		return true;
	}

	#else
	extern BOOL APIENTRY _CRT_INIT(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);

	BOOL APIENTRY DllMainCRTStartup(HINSTANCE hinst, DWORD reason, LPVOID reserved )
	{
		g_hinstDLL = hinst;
		g_lpReserved = reserved;
		return true;
	}
	#endif
	#ifdef __cplusplus
	}
	#endif
#else
	#ifdef __cplusplus
	extern "C" {
	#endif

	#define C4D_MAIN __attribute__ ((visibility("default"))) Int32 c4d_main(Int32 action, void* p1, void* p2, void* p3)
	C4D_MAIN;

	#ifdef __cplusplus
	}
	#endif
#endif

Int32 InitOS(void* p);

Filename* path_storage;

C4D_MAIN	//(Int32 action, void* p1, void* p2, void* p3)
{
	static Int32 init_count = 0;

	switch (action)
	{
		case C4DPL_INIT_VERSION:
		{
#ifdef __FLOAT_32_BIT
			return C4DPL_VERSION | C4DPL_SINGLEPRECISION_PLUGIN;
#else
			return C4DPL_VERSION;
#endif
		}

		case C4DPL_INIT_SYS:
			init_count += 1;
			if (init_count == 1)
			{
				if (InitOS(p1) < API_VERSION)
					return C4DPL_ERROR_VERSION;
				#ifdef __PC
					#ifdef __WINCRTINIT
						_CRT_INIT(g_hinstDLL, DLL_PROCESS_ATTACH, g_lpReserved);
					#endif
				#elif defined __MAC
					// static initializers are called by __dyld_dlopen, nothing to do here
				#endif
				if (!p3)
					return C4DPL_ERROR_VERSION;

				path_storage = NewObjClear(Filename);
				if (path_storage)
					*path_storage = *(Filename*)p3;
			}
			return 1;

		case C4DPL_MESSAGE:
			if (!PluginMessage((Int)p1, p2))
				return C4DPL_ERROR;
			return 1;

		case C4DPL_INIT:
			return PluginStart();

		case C4DPL_END:
			init_count -= 1;
			if (init_count == 0)
			{
				PluginEnd();
				FreeResource();
				DeleteObj(path_storage);
				#ifdef __PC
					#ifdef __WINCRTINIT
						_CRT_INIT(g_hinstDLL, DLL_PROCESS_DETACH, g_lpReserved);
					#endif
				#elif defined __MAC
					// static destructors are called by __dyld_dlclose, nothing to do here
				#endif
			}
			return 1;

		default:
			break;
	}

	return C4DPL_ERROR;
}

