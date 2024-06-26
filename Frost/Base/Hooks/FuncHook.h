#pragma once

// This is an abstract base class for function hooks to inherit.
class FuncHook {
public:
	// This function initializes the hooks.
	virtual bool Initialize();
};

// Hooks Includes
#pragma region Hooks Include

// Input
#include "Input/KeymapHook.h"
#include "Input/MouseHook.h"

// Render
#include "Render/RenderContextHook.h"
#include "../DirectX/DirectXHook.h"

#pragma endregion


// This function initializes all registered function hooks
void InitializeHooks() {
	// This is an array of pointers to function hook objects
	static FuncHook* hooks[] = { // When you define a static in a method the variable will be created once you call the function but won't be modified if you call it again as its already been created
		&RenderContextHook::Instance(),
		&DirectXHook::Instance(),
		&KeymapHook::Instance(),
		&MouseHook::Instance(),
	};

	for (std::size_t i = 0; i < std::size(hooks); ++i) { // This will allow us to loop through our hooks.
		if (!hooks[i]->Initialize()) { // If a hooks didn't initialize.
			// Handle initialization failure (Which for now we'll ignore)
		}
	}
}