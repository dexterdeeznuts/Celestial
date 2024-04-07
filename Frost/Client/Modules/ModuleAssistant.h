#pragma once

#pragma region Module imports

#pragma endregion

// Sort the categories in the modules
void SortCategories() {
	for (Module* mod : modules) {
		if (std::find(categories.begin(), categories.end(), mod->getCategory()) == categories.end())
			categories.push_back(mod->getCategory());
	}
}

// Initialize and push all modules here.
void InitializeModules() {

}

void InitializeMods() {
	InitializeModules(); // Initialize modules.
	SortCategories(); // create categories
}

// Uninitialize modules.
void UninitializeMods() {
	for (auto mod : modules) {
		if (mod->isEnabled()) // If a module is enabled.
			mod->toggle(); // Disable the module.

		delete mod;
	}
}