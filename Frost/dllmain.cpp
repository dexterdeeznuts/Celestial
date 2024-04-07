// dllmain.cpp : Defines the entry point for the DLL application.

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

