#pragma once

namespace Address {
	static MinecraftUIRenderContext* renderContext = nullptr; // RenderContext
	static FontRepos* Font = nullptr; // Font Repos

	static MinecraftUIRenderContext* getRenderContext() { return renderContext; }
	static FontRepos* getFont() { return Font; }
}