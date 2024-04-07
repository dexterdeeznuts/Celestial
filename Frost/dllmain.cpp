// dllmain.cpp : Defines the entry point for the DLL application.

#pragma region Includes
// C++ Includes
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE module, DWORD  reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded when the DLL is first attached to the process
        DisableThreadLibraryCalls(module); // Give it the module of the dll.
    }
    return TRUE;
}

