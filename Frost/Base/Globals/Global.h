#pragma once

// You might use this if you want to group all of your global variables,
// functions, etc. under a common name to make them easier to find and organize
namespace Global {
	std::map<uint64_t, bool> Keymap = {}; // Keymap for key checks.

	namespace RenderInfo {
		static HWND Window = nullptr;
	}
}