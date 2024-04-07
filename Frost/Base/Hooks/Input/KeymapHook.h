#pragma once

// Declare a void pointer(Empty object) called onSendKey which is the CallBack for keymapDetourHook.
void* onSendKey; // Defined an orignal for Keymap.

void KeymapDetourHook(__int32 key, bool held) // Checks what key has been pressed and if its currently being held.
{
	// Set the value of Global::keymap[key] equal to held.
	Global::Keymap[key] = held;

	// Log the string "Key " concatenated with the value of key, a space, the string " ", and the value of held, followed by a newline character.
	// Debug code that you can remove.
	log(Utils::combine("Key", key, " ", held, "\n").c_str());

	// Inside our functiion we're calling the original code that was there/the original function we hooked so the games behavior doesn't change.
	Utils::CallFunc<void*, __int32, bool>( // CallFunc to call the original.
		onSendKey, key, held
	);
}

class KeymapHook : public FuncHook { // a Keymap class that inherits the FuncHook template we made
public:
	//
	bool Initialize() override // Now override the Initialize function so we can actually hook our stuff
	{
		// Using the utils class findSig function to locate the address of the signature
		// Find the address of the function specified by the signature "48 83 EC ? ? ? C1 4C 8D 05" and store it in a void pointer called keymapAddr
		
		// Key::feed
		void* KeymapAddr = Utils::findSig("48 83 EC ? ? ? C1 4C 8D 05");

		// Give it the address/ptr to the Keymap function.
		// Give it the detour ptr and then the original callback ptr.

		// Usage: (Sig/Address/Offset, Detour, Original Callback, HookName).
		// Don't forget to return its result.

		// Attempt to hook the function at the address stored in keymapAddr by replacing it with the address of keymapDetour and store the original function's address in onSendKey
		return Utils::HookFunction(KeymapAddr, (void*)&KeymapDetourHook, &onSendKey, "Keymap");

		return true;
	}

	static KeymapHook& Instance() { // a class setup function called Instance.
		static KeymapHook instance;
		return instance;
	}
};