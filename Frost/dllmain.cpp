// dllmain.cpp : Defines the entry point for the DLL application.

#pragma region Includes

// C++ Includes
#include <Windows.h>

#pragma endregion

// This function initializes the client.
void InitializeClient() { // A method called "InitializeClient" to initialize hooks/modules etc.

}

BOOL APIENTRY DllMain(HMODULE module, DWORD  reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded when the DLL is first attached to the process
        DisableThreadLibraryCalls(module); // Give it the module of the dll.

        // Create a new thread to initialize the client on using the CreatThread function C++ provides
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitializeClient, module, 0, nullptr);
    }
    return TRUE;
}

