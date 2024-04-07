// dllmain.cpp : Defines the entry point for the DLL application.

bool isRunning = true; // isRunning bool for ejection/detachment

#pragma region Includes

// C++ Includes
// C++ Includes
#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <filesystem>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

// Module List
class Module;
std::vector<Module*> modules = std::vector<Module*>();
std::vector<std::string> categories;

// DirectX
#include <d2d1.h>
#include <d2d1_2.h>
#include <dwrite.h>
#include <d3d12.h>
#include <d3d11on12.h>
#include <dxgi1_4.h>
#include <d2d1_3.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

// MinHook
#include "Libs/minhook/MinHook.h"

// ImGui & Kiero
#include "Libs/kiero/kiero.h"
#include "Libs/imgui/imgui.h"
#include "Libs/imgui/impl/imgui_impl_win32.h"
#include "Libs/imgui/impl/imgui_impl_dx11.h"
#include "Libs/imgui/impl/imgui_impl_dx12.h"

// Utils
#include "Base/Globals/Global.h"
#include "Base/Utils/Utils.h"

class MinecraftUIRenderContext;

// Maths
#include "Base/Utils/Maths/TextFormat.h"
#include "Base/Utils/Maths/TextHolder.h"
#include "Base/Utils/Maths/UIColor.h"
#include "Base/Utils/Maths/Vector2.h"
#include "Base/Utils/Maths/Vector3.h"
#include "Base/Utils/Maths/Vector4.h"

// SDK (Software Development Kit)
#include "Base/SDK/Core/Font.h"

// Address
#include "Base/Globals/Address.h"

// RenderUtil
#include "Base/Utils/RenderUtils.h" // This must be under SDK to avoid errors

// Event
#include "Client/Events/Event.h"

// Module
#include "Client/Modules/Module.h"

// Hooks
#include "Base/Hooks/FuncHook.h"

// ModuleAssistant
#include "Client/Modules/ModuleAssistant.h"

#pragma endregion

// This function initializes the client.
void InitializeClient() { // A method called "InitializeClient" to initialize hooks/modules etc.
    InitializeMods(); // This is used to initialize modules & sort categories.
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
    kiero::shutdown();
    MH_DisableHook(MH_ALL_HOOKS); // Disable all Hooks.
    MH_RemoveHook(MH_ALL_HOOKS); // Remove all Hooks.
    UninitializeMods(); // Disable all modules.
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

