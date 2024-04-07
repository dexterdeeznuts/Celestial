// dllmain.cpp : Defines the entry point for the DLL application.

bool isRunning = true; // isRunning bool for ejection/detachment

#pragma region Includes

// C++ Includes
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

// MinHook
#include "Libs/minhook/MinHook.h"

// Utils
#include "Base/Globals/Global.h"
#include "Base/Utils/Utils.h"

// Maths
#include "Base/Utils/Maths/TextFormat.h"
#include "Base/Utils/Maths/TextHolder.h"
#include "Base/Utils/Maths/UIColor.h"
#include "Base/Utils/Maths/Vector2.h"
#include "Base/Utils/Maths/Vector3.h"
#include "Base/Utils/Maths/Vector4.h"

// Hooks
#include "Base/Hooks/FuncHook.h"

#pragma endregion

// This function initializes the client.
void InitializeClient() { // A method called "InitializeClient" to initialize hooks/modules etc.
    InitializeHooks(); // This is used to initialize hooks to the proccess.
}

DWORD APIENTRY ejectThread(HMODULE lpParam)
{
    while (isRunning) { // When the client is running.
        // When Control and L pressed.
        if ((Global::Keymap[VK_CONTROL] && Global::Keymap['L'])) {
            // set bool isRunning to false. for ejection.
            isRunning = false;  // Uninject
        }
        Sleep(0); // I use this to avoid little decreasing in fps.
    }

    Sleep(50); // Sleep for a little bit.
    MH_DisableHook(MH_ALL_HOOKS); // Disable all Hooks.
    MH_RemoveHook(MH_ALL_HOOKS); // Remove all Hooks.
    FreeLibraryAndExitThread(lpParam, 1); // Uninject the client completly.
}

BOOL APIENTRY DllMain(HMODULE module, DWORD  reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        // Prevent the DLL from being unloaded when the DLL is first attached to the process
        DisableThreadLibraryCalls(module); // Give it the module of the dll.

        // Create a new thread to initialize the client on using the CreatThread function C++ provides
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitializeClient, module, 0, nullptr);

        // Create a new thread for ejection using the CreatThread function C++ provides
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ejectThread, module, 0, 0);
    }
    return TRUE;
}

